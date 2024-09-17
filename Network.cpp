#include <Network.hpp>

#include <SunRise.hpp>
#include <WeatherData.hpp>

#include <QJsonArray>
#include <QJsonObject>
#include <QDomDocument>
#include <QJsonDocument>

#include <QNetworkReply>
#include <QNetworkAccessManager>

#include <QFile>
#include <QTextStream>

#include <vector>

using namespace std;

Network::Network(QObject *parent)
    : QObject(parent)
    , m_manager(new QNetworkAccessManager(this))
{
    connect(m_manager, &QNetworkAccessManager::finished,
            this, &Network::replyFinished);
}
Network::~Network()
{}

void Network::getLocalizationInfo(const QString &city)
{
    if (!m_localizationReply.isNull())
    {
        m_localizationReply->abort();
    }
    m_localizationReply = m_manager->get(QNetworkRequest(QUrl(QString("https://nominatim.openstreetmap.org/search?city=%1&format=json").arg(city))));
}

void Network::getWeatherInfo(const QString &lat, const QString &lon)
{
    if (!m_weatherReply.isNull())
    {
        m_weatherReply->abort();
    }

    QString apiVersion = "2.0";

    QNetworkRequest request(QUrl(QString("https://api.met.no/weatherapi/locationforecast/%1/classic?lat=%2&lon=%3")
                                                             .arg(apiVersion, lat, lon)));
    request.setRawHeader("User-Agent", "Mozilla/5.0 (X11; Linux x86_64; rv:130.0) Gecko/20100101 Firefox/130.0");
    m_weatherReply = m_manager->get(request);
}

void Network::getSunriseReply(const QString &lat, const QString &lon, const QDate date, const QTime offset)
{
    if (!m_sunriseReply.isNull())
    {
        m_sunriseReply->abort();
    }

    const QString apiVersion = "3.0";

    m_sunriseReply = m_manager->get(QNetworkRequest(QUrl(QString("https://api.met.no/weatherapi/sunrise/%1/.json?lat=%2&lon=%3&date=%4&offset=%5")
                                                         .arg(apiVersion).arg(lat).arg(lon).arg(date.toString("yyyy-MM-dd")).arg(offset.toString("hh:mm")))));
}

void Network::getIcon(int symbol, bool isNight)
{
    if (!m_iconReply.isNull())
    {
        m_iconReply->abort();
    }

    QString apiVersion = "1.1";

    m_iconReply = m_manager->get(QNetworkRequest(QUrl(QString("https://api.met.no/weatherapi/weathericon/%1/?symbol=%2&is_night=%3&content_type=image/svg%4Bxml")
                                                      .arg(apiVersion).arg(symbol).arg(QString::number(isNight)).arg("%2"))));
}


void Network::replyFinished(QNetworkReply *reply)
{
    if (reply->error())
    {
        if (reply->error() != QNetworkReply::OperationCanceledError)
            qWarning() << reply->errorString();
    }
    else if (reply == m_sunriseReply)
    {
        parseSunrise(reply->readAll());
    }
    else if (reply == m_weatherReply)
    {
        parseWeather(reply->readAll());
    }
    else if (reply == m_localizationReply)
    {
        parseLocalization(reply->readAll());
    }
    else if (reply == m_iconReply)
    {
        parseIcon(reply->readAll());
    }
    reply->deleteLater();
}

void Network::parseSunrise(const QByteArray &xmlData)
{
    vector<SunRise> rise;

    const QJsonDocument doc = QJsonDocument::fromJson(xmlData);
    if (doc.isNull())
    {
        qWarning() << "Json doc is null!";
        return;
    }

    const QJsonObject obj = doc.object();

    auto longitude = obj["location"]["longitude"].toString();
    auto latitude = obj["location"]["latitude"].toString();

    const QJsonArray arr = obj["location"]["time"].toArray();

    for (const QJsonValue &data : arr)
    {
        const QJsonObject obj = data.toObject();

        if (obj.isEmpty())
            continue;

        rise.push_back(SunRise::sunRiseParser(longitude, latitude, obj));
    }
    emit sunRiseInfo(rise);
}

void Network::parseWeather(const QByteArray &xmlData)
{
    QDomDocument xml;
    QString errMsg;
    if (!xml.setContent(xmlData, &errMsg))
    {
        qWarning() << errMsg;
        return;
    }
    auto data = WeatherData::weatherParser(xml);

    emit weatherInfo(data);
}

void Network::parseIcon(const QByteArray &svgData)
{
    emit iconInfo(svgData);
}

void Network::parseLocalization(const QByteArray &xmlData)
{
    vector<WeatherLocalization> localizationVector;

    const QJsonDocument doc = QJsonDocument::fromJson(xmlData);
    if (doc.isNull())
    {
        qWarning() << "Json doc is null!";
        return;
    }

    const QJsonArray arr = doc.array();
    localizationVector.reserve(arr.count());
    for (const QJsonValue &data : arr)
    {
        const QJsonObject obj = data.toObject();
        if (obj.isEmpty())
            continue;

        localizationVector.push_back(WeatherLocalization::localizationParser(obj));
    }
    emit localization(localizationVector);
}

#pragma once

#include <QPointer>
#include <QDateTime>

#include <WeatherData.hpp>
#include <WeatherLocalization.hpp>

class SunRise;
class WeatherData;

class QNetworkReply;
class QNetworkAccessManager;

class Network : public QObject
{
    Q_OBJECT

public:
    Network(QObject *parent = nullptr);
    ~Network();

    void getLocalizationInfo(const QString &city);
    void getWeatherInfo(const QString &lat, const QString &lon);
    void getSunriseReply(const QString &lat, const QString &lon, const QDate date, const QTime offset);
    void getIcon(int symbol, bool isNight);

signals:
    void localization(const std::vector<WeatherLocalization> &data);
    void weatherInfo(const std::vector<WeatherData> &data);
    void sunRiseInfo(const std::vector<SunRise> &data);
    void iconInfo(const QByteArray &);

private:
    void replyFinished(QNetworkReply *reply);

    void parseSunrise(const QByteArray &xmlData);
    void parseWeather(const QByteArray &xmlData);
    void parseIcon(const QByteArray &svgData);

    void parseLocalization(const QByteArray &xmlData);

private:
    QNetworkAccessManager *const m_manager;
    QPointer<QNetworkReply> m_sunriseReply;
    QPointer<QNetworkReply> m_weatherReply;
    QPointer<QNetworkReply> m_iconReply;

    QPointer<QNetworkReply> m_localizationReply;

    QDate m_date;

    double m_latitude = qQNaN();
    double m_longitude = qQNaN();
    QDateTime m_sunrise, m_sunset;

    QString m_moonPhase;
    QDateTime m_moonrise, m_moonset;

};

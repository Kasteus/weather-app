#include "WeatherDisplay.hpp"

#include <QTabWidget>
#include <WeatherDays.hpp>
#include <WeatherDayAdvance.hpp>
#include <QTimer>

#include <QDebug>

#include <QStyle>
#include <QScrollBar>

#include <QSettings>

WeatherDisplay::WeatherDisplay(QWidget *parent)
    : QTabWidget(parent)
{
    m_days = new WeatherDays;
    m_dayAdvance = new WeatherDayAdvance;

    addTab(m_days, "Weather");
    addTab(m_dayAdvance, "Advanced");


    connect(&net, &Network::weatherInfo, this, &WeatherDisplay::setWeather);
    connect(&net, &Network::sunRiseInfo, this, &WeatherDisplay::setSunRise);

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout,
            this, [=] {
        qDebug() << m_time;
        qDebug() << "dupass";
        if (m_timer->interval() == 0 || m_timer->interval() != m_time)
            m_timer->setInterval(m_time);
        qDebug() << m_time << " " << m_timer->interval();

        net.getWeatherInfo(QString::number(m_lat),QString::number(m_lon));
        net.getSunriseReply(QString::number(m_lat), QString::number(m_lon), QDate::currentDate(), QTime(0, 0));
    });

    loadSettings();


    connect(m_dayAdvance, &WeatherDayAdvance::updateTooltipInfo, [=](const QStringList &toolTipInfo){
        emit updateTooltipInfo(toolTipInfo);
    });
}

void WeatherDisplay::setWeather(const std::vector<WeatherData> &data)
{
    m_days->setWeatherInfo(data);
    m_dayAdvance->setWeatherInfoAdvance(data);
}

void WeatherDisplay::setSunRise(const std::vector<SunRise> &data)
{
    m_days->setSunriseInfo(data);
    m_dayAdvance->setSunRiseInfoAdvance(data);
}

void WeatherDisplay::setLat(double value)
{
    m_lat = value;
}

void WeatherDisplay::setLon(double value)
{
    m_lon = value;
}

void WeatherDisplay::setTemperatureUnit(int value)
{
    m_dayAdvance->setTemperatureUnit(value);
    m_days->setTempUnit(value);
}

void WeatherDisplay::setPressureUnit(int value)
{
    m_dayAdvance->setPressureUnit(value);
}

void WeatherDisplay::setPrecissionUnit(int value)
{
    m_dayAdvance->setPrecissionUnit(value);
}

void WeatherDisplay::setWindUnit(int value)
{
     m_dayAdvance->setWindUnit(value);
     m_days->setWindUnit(value);
}

void WeatherDisplay::setAltUnit(int value)
{
    m_dayAdvance->setAltUnit(value);
}

void WeatherDisplay::setAppTemp(int value)
{
    m_dayAdvance->setAppTemp(value);
}


void WeatherDisplay::setLayout(int idx)
{
    idx ? m_days->verticalLayout() : m_days->horizontalLayout();
}

void WeatherDisplay::setNumberOfDays(int days)
{
    m_days->setNumberOfDays(days);
}

void WeatherDisplay::setTimer(int time, bool locationChanged)
{
//    if (timer->isActive())
//        timer->stop();
//    qDebug() << timer->remainingTime() << time * 1000;
    if (!m_timer->isActive() || locationChanged)
    {
        qDebug() << time << " dupa";
        m_time = time * 1000;
        m_timer->start(0);
        return;
    }

    qDebug() << m_timer->remainingTime();
    if (m_timer->remainingTime() > time * 1000)
    {
//        qDebug() << m_time << timer->interval() << timer->remainingTime();
        m_time = time * 1000;
        qDebug() << " cyc" << m_time;;
        m_timer->start(m_time);
    }
    else
    {
        m_time = m_timer->remainingTime();
//        qDebug() << m_time << timer->interval() << timer->remainingTime();
        m_timer->start(m_time);
        m_time = time * 1000;
    }



//    if (timer)
//    {
//        timer->start(m_time);
//    }
}

WeatherDisplay::~WeatherDisplay()
{}

void WeatherDisplay::loadSettings()
{
    double lat = m_lat;
    double lon = m_lon;
    bool locationChanged = false;

    setLat(settings.value("Location/lat").toDouble());
    setLon(settings.value("Location/lon").toDouble());
    setTemperatureUnit(settings.value("Unit/temperature").toInt());
    setPressureUnit(settings.value("Unit/barometricPress").toInt());
    setPrecissionUnit(settings.value("Unit/precipitations").toInt());
    setWindUnit(settings.value("Unit/windSpeed").toInt());
    setAltUnit(settings.value("Unit/altitude").toInt());
    setAppTemp(settings.value("Unit/apperentTemp").toInt());
    setLayout(settings.value("Apperance/arrangement").toInt());
    setNumberOfDays(settings.value("Apperance/numberDays").toInt());

    if (lat != m_lat || lon != m_lon)
    {
        locationChanged = true;
    }

    setTimer(settings.value("Apperance/refreshTime").toInt(), locationChanged);

\
}

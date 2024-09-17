#pragma once

#include <QTabWidget>
#include <QDateTime>

#include <WeatherData.hpp>
#include <Network.hpp>
#include <QSettings>

class WeatherDays;
class SunRise;
class WeatherDayAdvance;
class QTimer;

class WeatherDisplay: public QTabWidget
{
    Q_OBJECT

public:
    WeatherDisplay(QWidget *parent = nullptr);
    ~WeatherDisplay();


signals:
    void getSunriseReply(const QString &lat, const QString &lon, const QDate date, const QTime offset);
    void getWeatherInfo(const QString &lat, const QString &lon);
    void updateTooltipInfo(const QStringList &toolTipInfo);

public slots:
    void setWeather(const std::vector<WeatherData> &data);
    void setSunRise(const std::vector<SunRise> &data);

public:
    void loadSettings();
    void setLat(double value);
    void setLon(double value);
    void setTemperatureUnit(int value);
    void setPressureUnit(int value);
    void setPrecissionUnit(int value);
    void setWindUnit(int value);
    void setAltUnit(int value);
    void setAppTemp(int value);
    void setLayout(int idx);
    void setNumberOfDays(int days);
    void setTimer(int time, bool locationChanged);

public:
    WeatherDays *m_days = nullptr;
    WeatherDayAdvance *m_dayAdvance = nullptr;;

    QTimer *m_timer = nullptr;

    double m_lat = 0;
    double m_lon = 0;
    int m_time = 10000;

    Network net;

    QSettings settings;

};

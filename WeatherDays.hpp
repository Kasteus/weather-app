#pragma once

#include <QScrollArea>
#include <QDateTime>

class Network;
class QDateTime;
class WeatherDay;
class WeatherData;
class QGridLayout;
class SunRise;

class WeatherDays : public QScrollArea
{
    Q_OBJECT

public:
    struct DaysInformation
    {
        QDateTime dateFrom;
        QDateTime dateTo;
        QString cloudness;
        QString temp;
        QString windSpeed;
        int sybmol = 0;
    };

    WeatherDays(QWidget *parent = nullptr);
    ~WeatherDays();

    void initWindow();
    const QStringList getDayNames() const;

    void readIcons();
    void setWeatherData();
    void setNumberOfDays(int i);

    void verticalLayout();
    void horizontalLayout();

    void setWeatherInfo(const std::vector<WeatherData> &data);
    void setSunriseInfo(const std::vector<SunRise> &data);

    void setTempUnit(int idx);
    void setWindUnit(int idx);

private:
    QGridLayout *createLayout(int direction);

private:
    QSize sizeHint() const override;

public:
    QStringList m_daysHourTime;
    QStringList m_daysName;
    std::vector<WeatherDay *> m_daysData;

    std::vector<QByteArray> m_iconDay;
    std::vector<QByteArray> m_iconNight;

    uint32_t m_days = 6;

    bool m_night = false;

    std::vector<DaysInformation> m_daysInfo;

    int m_layoutDirection;
    int m_tempUnit = 0;
    int m_windUnit = 0;
};

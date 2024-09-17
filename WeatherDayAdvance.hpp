#pragma once

#include <QWidget>
#include <QTextEdit>

#include <memory>

class WeatherData;
class SunRise;

class WeatherDayAdvance : public QTextEdit
{
    Q_OBJECT

    struct Info;

public:
    WeatherDayAdvance(QWidget *parent = nullptr);
    ~WeatherDayAdvance();

    void updateInformation();

    void setWeatherInfoAdvance(const std::vector<WeatherData> &data);
    void setSunRiseInfoAdvance(const std::vector<SunRise> &data);
    void setTemperatureUnit(int idx);
    void setPressureUnit(int idx);
    void setPrecissionUnit(int idx);
    void setWindUnit(int idx);
    void setAltUnit(int idx);
    void setAppTemp(int idx);

signals:
    void updateTooltipInfo(const QStringList &toolTipInfo);

public:
    const std::unique_ptr<Info> m_info;
};

#include "WeatherDayAdvance.hpp"
#include <WeatherData.hpp>
#include <SunRise.hpp>

#include <QTextEdit>
#include <QDebug>
#include <cmath>

#include <Unit.hpp>

#include <QScrollBar>

using namespace std;

struct WeatherDayAdvance::Info
{
    QString altitude;
    QString latitude;
    QString longitude;

    QString temperatureValue;
    QString temperatureUnit;
    QString dewpointTemperatureValue;
    QString dewpointTemperatureUnit;

    QString windSpeedMps;
    QString windSpeedName;
    QString windDirectionDeg;
    QString windDirectionName;
    QString windSpeedBeaufort;

    QString pressureValue;
    QString pressureUnit;
    QString humidityValue;
    QString humidityUnit;

    QString fogPercent;
    QString lowCloudsPercent;
    QString mediumCloudsPercent;
    QString highCloudsPercent;
    QString cloudniessPercent;

    QString precipitationValue;
    QString precipitationUnit;

    QString sunrise;
    QString sunset;
    QString moonrise;
    QString moonset;

    QString windUnit;
    QString altitudeUnit;

    int tempUnit = 0;
    int pressUnit = 0;
    int windSpeedUnit = 0;
    int precUnit = 0;
    int altUnit = 0;
    int appTemp = 0;
};

/**/

WeatherDayAdvance::WeatherDayAdvance(QWidget *parent)
    : QTextEdit(parent)
    , m_info(make_unique<Info>())
{
    setReadOnly(true);
    viewport()->setCursor(QCursor());
//    updateInformation();
}
WeatherDayAdvance::~WeatherDayAdvance()
{}

void WeatherDayAdvance::updateInformation()
{

    QString tempVal, tempUnit, dewVal, dewUnit, pressVal, pressUnit, precVal, precUnit, windVal, windUnit, altVal, altUnit, appTemp;
    switch (m_info->tempUnit)
    {
        case Unit::Temperature::Celsius:
            tempVal = m_info->temperatureValue;
            tempUnit = " \u2103";
            dewVal = m_info->dewpointTemperatureValue;
            dewUnit = " \u2103";
            break;
        case Unit::Temperature::Farenheit:
            tempVal = QString::number((m_info->temperatureValue.toDouble() * 1.8) + 32, 'G', 3);
            tempUnit = " \u2109";
            dewVal = QString::number((m_info->dewpointTemperatureValue.toDouble() * 1.8) + 32, 'G', 3);
            dewUnit = " \u2109";
            break;
        case Unit::Temperature::Kelvin:
            tempVal = QString::number(m_info->temperatureValue.toDouble() + 273.15, 'G', 3);
            tempUnit = " K";
            dewVal = QString::number(m_info->dewpointTemperatureValue.toDouble() + 273.15, 'G', 3);
            dewUnit = " K";
            break;
    }

    switch (m_info->pressUnit)
    {
        case Unit::Pressure::Hectopascal:
            pressVal = m_info->pressureValue;
            pressUnit = " hPa";
            break;
        case Unit::Pressure::InchMercury:
            pressVal = QString::number(m_info->pressureValue.toDouble() * 0.4016064257, 'G', 3);
            pressUnit = " inHg";
            break;
        case Unit::Pressure::PoundForce:
            pressVal = QString::number(m_info->pressureValue.toDouble() * 0.0145037738, 'G', 3);
            pressUnit = " psi" ;
            break;
        case Unit::Pressure::Torr:
            pressVal = QString::number(m_info->pressureValue.toDouble() * 0.7500616738, 'G', 3);
            pressUnit = " mmHg";
            break;
    }

    switch (m_info->precUnit)
    {
        case Unit::Precipiation::Milimeters:
            precVal = m_info->precipitationValue;
            precUnit = " mm";
            break;
        case Unit::Precipiation::Inches:
            precVal = QString::number(m_info->precipitationValue.toDouble() * 0.0393700787401575, 'G', 3);
            precUnit = " ft";
            break;
    }

    switch (m_info->windSpeedUnit)
    {
        case Unit::Wind::Km_h:
            windVal = QString::number(m_info->windSpeedMps.toDouble() * 3.6, 'G', 3);
            windUnit = " km/h";
            break;
        case Unit::Wind::Mp_h:
            windVal = QString::number(m_info->windSpeedMps.toDouble() * 2.24, 'G', 3);
            windUnit = " mph";
            break;
        case Unit::Wind::M_s:
            windVal = QString::number(m_info->windSpeedMps.toDouble(), 'G', 3);
            windUnit = " m/s";
            break;
        case Unit::Wind::Ft_s:
            windVal = QString::number(m_info->windSpeedMps.toDouble() * 3.280839895013, 'G', 3);
            windUnit = " ft/s";
            break;
        case Unit::Wind::Kt:
            windVal = QString::number(m_info->windSpeedMps.toDouble() * 1.943844492441, 'G', 3);
            windUnit = " Kt";
            break;
    }

    switch (m_info->altUnit)
    {
        case Unit::Altitude::Meter:
            altVal = m_info->altitude;
            altUnit = " m";
            break;
        case Unit::Altitude::Feet:
            altVal = QString::number(m_info->altitude.toDouble() * 3.2808399, 'G', 3);
            altUnit = " ft";
            break;
    }

    switch (m_info->appTemp)
    {
        case Unit::ApperentTemp::Heat:
        {
            double temp = m_info->temperatureValue.toDouble() * 9.0 / 5.0 + 32;
            double humidity= m_info->humidityValue.toDouble();
            const double c1 = -42.379;
            const double c2 = 2.04901523;
            const double c3 = 10.14333127;
            const double c4 = -.22475541;
            const double c5 = -0.00683783;
            const double c6 = -0.05481717;
            const double c7 = 0.00122874;
            const double c8 = 0.00085282;
            const double c9 = -0.00000199;

            double heatIndex = c1 + (c2 * temp) +
                                   (c3 * humidity) +
                                   (c4 * temp*humidity) +
                                   (c5 * (temp*temp)) +
                                   (c6 * (humidity * humidity)) +
                                   (c7 * (temp * temp) * humidity) +
                                   (c8 * temp * (humidity * humidity)) +
                                   (c9 * (temp * temp) * (humidity * humidity));
            appTemp = QString::number(heatIndex, 'G', 3 );
        }
            break;
        case Unit::ApperentTemp::Chill:
            appTemp = QString::number(13.12 + (0.6215 * m_info->temperatureValue.toDouble()) - (11.37*pow(m_info->windSpeedMps.toDouble() * 3.6, 0.16)) + (0.3965 * m_info->temperatureValue.toDouble() * pow(m_info->windSpeedMps.toDouble() * 3.6, 0.16)), 'G', 3);
            break;
    }

    //TODO apparent temperature
    setHtml(
        "<pre>"
            "<p><strong>Coordinates</strong><br/>"
            "    Altitude: " + altVal + altUnit+ "<br/>"
            "    Latitude: " + m_info->latitude + "<br/>"
            "    Longtitude: " + m_info->longitude + "<br/>"
            "</p>"
            "<p><strong>Astronomical data</strong><br/>"
            "    Sunrise:  " + m_info->sunrise + "<br/>"
            "    Sunset:   " + m_info->sunset + "<br/>"
            "    Moonrise: " + m_info->moonrise + "<br/>"
            "    Moonset:  " + m_info->moonset + "<br/>"
            "</p>"
            "<p><strong>Temperatures</strong><br/>"
            "    Temperature: " + tempVal + tempUnit + "<br/>"
            "    Dew point: " + dewVal + dewUnit + "<br/>"
            "    Apparent temperature: " + appTemp + "<br/>"
            "</p>"
            "<p><strong>Wind</strong><br/>"
            "    Speed: " + windVal + windUnit + "<br/>"
            "    Direction: " + m_info->windDirectionDeg + "<br/>"
            "</p>"
            "<p><strong>Percipitation</strong><br/>"
            "    Percipitation ammount: " + precVal + precUnit + "<br/>"
            "</p>"
            "<p><strong>Atmosphere</strong><br/>"
            "    Barometric pressure: " + pressVal + pressUnit + "<br/>"
            "    Relative humidity: " + m_info->humidityValue + "%<br/>"
            "</p>"
            "<p><strong>Clouds</strong><br/>"
            "    Fog: " + m_info->fogPercent + "%<br/>"
            "    Low clouds: " + m_info->lowCloudsPercent + "%<br/>"
            "    Middle clouds: " + m_info->mediumCloudsPercent + "%<br/>"
            "    High clouds: " + m_info->highCloudsPercent + "%<br/>"
            "    Cloudiness: " + m_info->cloudniessPercent + "%<br/>"
            "</p>"
        "</pre>"
    );
    QStringList tooltipInfo;
    tooltipInfo.push_back(m_info->latitude);
    tooltipInfo.push_back(m_info->longitude);
    tooltipInfo.push_back(altVal + altUnit);
    tooltipInfo.push_back(m_info->cloudniessPercent + "%");
    tooltipInfo.push_back(tempVal + tempUnit);
    tooltipInfo.push_back(windVal + windUnit);
    tooltipInfo.push_back(m_info->windSpeedName);
    tooltipInfo.push_back(m_info->windDirectionDeg);
    tooltipInfo.push_back(m_info->windDirectionName);
    tooltipInfo.push_back(pressVal + pressUnit);
    tooltipInfo.push_back(m_info->humidityValue + "%");
    emit updateTooltipInfo(tooltipInfo);

}

void WeatherDayAdvance::setWeatherInfoAdvance(const vector<WeatherData> &data)
{
    auto date = QDateTime::currentDateTimeUtc();

    bool found = false;

    for (auto &&weatherItem : data)
    {
        if (found)
        {
            m_info->precipitationValue = QString::number(weatherItem.precipitationValue);
            m_info->precipitationUnit = weatherItem.precipitationUnit;
            break;
        }

        if (!found && weatherItem.timeTo > date && weatherItem.timeTo == weatherItem.timeFrom)
        {
            m_info->altitude = QString::number(weatherItem.altitude);
            m_info->latitude = QString::number(weatherItem.latitude);
            m_info->longitude = QString::number(weatherItem.longitude);

            m_info->temperatureValue = QString::number(weatherItem.temperatureValue);
            m_info->temperatureUnit = weatherItem.temperatureUnit;
            m_info->dewpointTemperatureValue = QString::number(weatherItem.dewpointTemperatureValue);
            m_info->dewpointTemperatureUnit = weatherItem.dewpointTemperatureUnit;

            m_info->windSpeedMps = QString::number(weatherItem.windSpeedMps);
            m_info->windSpeedName = weatherItem.windSpeedName;
            m_info->windDirectionDeg = QString::number(weatherItem.windDirectionDeg);
            m_info->windDirectionName = weatherItem.windDirectionName;
            m_info->windSpeedBeaufort = QString::number(weatherItem.windSpeedBeaufort);

            m_info->pressureValue = QString::number(weatherItem.pressureValue);
            m_info->pressureUnit = weatherItem.pressureUnit;
            m_info->humidityValue = QString::number(weatherItem.humidityValue);
            m_info->humidityUnit = weatherItem.humidityUnit;

            m_info->fogPercent = QString::number(weatherItem.fogPercent);
            m_info->lowCloudsPercent = QString::number(weatherItem.lowCloudsPercent);
            m_info->mediumCloudsPercent = QString::number(weatherItem.mediumCloudsPercent);
            m_info->highCloudsPercent = QString::number(weatherItem.highCloudsPercent);
            m_info->cloudniessPercent = QString::number(weatherItem.cloudniessPercent);

            found = true;
        }
    }

    updateInformation();
}

void WeatherDayAdvance::setSunRiseInfoAdvance(const vector<SunRise> &data)
{
    m_info->sunset = data[0].sunsetTime.toString("yyyy-MM-dd hh:mm");
    m_info->sunrise = data[0].sunriseTime.toString("yyyy-MM-dd hh:mm");
    m_info->moonset = data[0].moonsetTime.toString("yyyy-MM-dd hh:mm");
    m_info->moonrise = data[0].moonriseTime.toString("yyyy-MM-dd hh:mm");
    updateInformation();
}

void WeatherDayAdvance::setTemperatureUnit(int idx)
{
    m_info->tempUnit = idx;
    updateInformation();
}

void WeatherDayAdvance::setPressureUnit(int idx)
{
    m_info->pressUnit = idx;
    updateInformation();
}

void WeatherDayAdvance::setPrecissionUnit(int idx)
{
    m_info->precUnit = idx;
    updateInformation();
}

void WeatherDayAdvance::setWindUnit(int idx)
{
    m_info->windSpeedUnit = idx;
    updateInformation();
}

void WeatherDayAdvance::setAltUnit(int idx)
{
    m_info->altUnit = idx;
    updateInformation();
}

void WeatherDayAdvance::setAppTemp(int idx)
{
    m_info->appTemp = idx;
    updateInformation();
}

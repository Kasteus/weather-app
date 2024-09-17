#pragma once

#include <QObject>
#include <QDateTime>

class QString;
class QDomDocument;

using namespace std;

class WeatherData
{
public:
    static vector<WeatherData> weatherParser(const QDomDocument &xml);

public:
    QDateTime   timeFrom;
    QDateTime   timeTo;
    double      altitude;
    double      latitude;
    double      longitude;
    QString     temperatureUnit;
    double      temperatureValue;
    double      windDirectionDeg;
    QString     windDirectionName;
    double      windSpeedMps;
    int         windSpeedBeaufort;
    QString     windSpeedName;
    double      humidityValue;
    QString     humidityUnit;
    QString     pressureUnit;
    double      pressureValue;
    double      cloudniessPercent;
    double      fogPercent;
    double      lowCloudsPercent;
    double      mediumCloudsPercent;
    double      highCloudsPercent;
    QString     dewpointTemperatureUnit;
    double      dewpointTemperatureValue;
    QString     minTemperatureUnit;
    double      minTemperatureValue;
    QString     maxTemperatureUnit;
    double      maxTemperatureValue;
    QString     precipitationUnit;
    double      precipitationValue;
    QString     symbol;
    int         symbolID;
};

#include "WeatherData.hpp"

#include <QDomDocument>
#include <QDomNodeList>

vector<WeatherData> WeatherData::weatherParser(const QDomDocument &xml)
{
    vector<WeatherData> wData;

    const QDomElement element = xml.documentElement();
    const QDomElement productElement = element.firstChildElement("product");

    QDomNodeList nodes = productElement.elementsByTagName("time");
    for (int i = 0; i < nodes.count(); ++i)
    {
        QDomNode element = nodes.at(i);
        if (!element.isElement())
            continue;

        const QDomElement timeElement = element.toElement();
        const QDomElement locationElement = timeElement.toElement().firstChildElement("location");
        const QDomElement temperatureElement = locationElement.firstChildElement("temperature");
        const QDomElement windDirectionElement = locationElement.firstChildElement("windDirection");
        const QDomElement windSpeedElement = locationElement.firstChildElement("windSpeed");
        const QDomElement humidityElement = locationElement.firstChildElement("humidity");
        const QDomElement pressureElement = locationElement.firstChildElement("pressure");
        const QDomElement cloudinessElement = locationElement.firstChildElement("cloudiness");
        const QDomElement fogElement = locationElement.firstChildElement("fog");
        const QDomElement lowCloudsElement = locationElement.firstChildElement("lowClouds");
        const QDomElement mediumCloudsElement = locationElement.firstChildElement("mediumClouds");
        const QDomElement highCloudsElement = locationElement.firstChildElement("highClouds");
        const QDomElement dewpointTemperatureElement = locationElement.firstChildElement("dewpointTemperature");
        const QDomElement minTemperatureElement = locationElement.firstChildElement("minTemperature");
        const QDomElement maxTemperatureElement = locationElement.firstChildElement("maxTemperature");
        const QDomElement precipitationElement = locationElement.firstChildElement("precipitation");
        const QDomElement symbol = locationElement.firstChildElement("symbol");

        wData.push_back({
            .timeFrom = QDateTime::fromString(timeElement.toElement().attribute("from"), Qt::ISODate),
            .timeTo = QDateTime::fromString(timeElement.toElement().attribute("to"), Qt::ISODate),
            .altitude = locationElement.attribute("altitude").toDouble(),
            .latitude = locationElement.attribute("latitude").toDouble(),
            .longitude = locationElement.attribute("longitude").toDouble(),
            .temperatureUnit = temperatureElement.attribute("unit"),
            .temperatureValue = temperatureElement.attribute("value").toDouble(),
            .windDirectionDeg = windDirectionElement.attribute("deg").toDouble(),
            .windDirectionName = windDirectionElement.attribute("name"),
            .windSpeedMps = windSpeedElement.attribute("mps").toDouble(),
            .windSpeedBeaufort = windSpeedElement.attribute("beaufort").toInt(),
            .windSpeedName = windSpeedElement.attribute("name"),
            .humidityValue = humidityElement.attribute("value").toDouble(),
            .humidityUnit = humidityElement.attribute("unit"),
            .pressureUnit = pressureElement.attribute("unit"),
            .pressureValue = pressureElement.attribute("value").toDouble(),
            .cloudniessPercent = cloudinessElement.attribute("percent").toDouble(),
            .fogPercent = fogElement.attribute("percent").toDouble(),
            .lowCloudsPercent = lowCloudsElement.attribute("percent").toDouble(),
            .mediumCloudsPercent = mediumCloudsElement.attribute("percent").toDouble(),
            .highCloudsPercent = highCloudsElement.attribute("percent").toDouble(),
            .dewpointTemperatureUnit = dewpointTemperatureElement.attribute("unit"),
            .dewpointTemperatureValue = dewpointTemperatureElement.attribute("value").toDouble(),
            .minTemperatureUnit = minTemperatureElement.attribute("unit"),
            .minTemperatureValue = minTemperatureElement.attribute("value").toDouble(),
            .maxTemperatureUnit = maxTemperatureElement.attribute("unit"),
            .maxTemperatureValue = maxTemperatureElement.attribute("value").toDouble(),
            .precipitationUnit = precipitationElement.attribute("unit"),
            .precipitationValue = precipitationElement.attribute("value").toDouble(),
            .symbol = symbol.attribute("id"),
            .symbolID = symbol.attribute("number").toInt(),
        });
    }

    return wData;
}

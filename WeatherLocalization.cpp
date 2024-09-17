#include "WeatherLocalization.hpp"

#include <QStringList>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

WeatherLocalization WeatherLocalization::localizationParser(const QJsonObject &obj)
{
    WeatherLocalization loc;

    loc.lat = obj["lat"].toString();
    loc.lon = obj["lon"].toString();
    loc.displayName = obj["display_name"].toString();

    loc.place = obj["place_id"].toString();
    loc.licence = obj["licence"].toString();
    loc.osm_type = obj["osm_type"].toString();
    loc.osm_id = obj["osm_id"].toString();

    for (const QJsonValueRef &value : obj["boundingbox"].toArray())
        loc.boundingbox += value.toString();

    loc.clas = obj["class"].toString();
    loc.type = obj["type"].toString();
    loc.importance = QString::number(obj["importance"].toDouble());
    loc.icon = obj["icon"].toString();

    return loc;
}

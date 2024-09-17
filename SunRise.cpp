#include "SunRise.hpp"

#include <QJsonDocument>
#include <QJsonObject>

SunRise SunRise::sunRiseParser(const QString &lon, const QString &lat, const QJsonObject &obj)
{
    SunRise rise {
        .latitude = lat,
        .longitude = lon,
        .sunsetTime = QDateTime::fromString(obj["sunset"]["time"].toString(), Qt::ISODate),
        .high_moonElevation = obj["high_moon"]["elevation"].toString(),
        .high_moonTime = QDateTime::fromString(obj["high_moon"]["time"].toString(), Qt::ISODate),
        .moonphaseValue = obj["moonphase"]["value"].toString(),
        .moonphaseTime = QDateTime::fromString(obj["moonphase"]["time"].toString(), Qt::ISODate),
        .sunriseTime = QDateTime::fromString(obj["sunrise"]["time"].toString(), Qt::ISODate),
        .moonriseTime = QDateTime::fromString(obj["moonrise"]["time"].toString(), Qt::ISODate),
        .solarnoonTime = QDateTime::fromString(obj["solarnoon"]["time"].toString(), Qt::ISODate),
        .solarmidnightElevation = obj["solarmidnight"]["elevation"].toString(),
        .solarmidnightTime = QDateTime::fromString(obj["solarmidnight"]["time"].toString(), Qt::ISODate),
        .moonpositionAzimuth = obj["moonposition"]["azimuth"].toString(),
        .moonpositionPhase = obj["moonposition"]["phase"].toString(),
        .moonpositionRange = obj["moonposition"]["range"].toString(),
        .low_moonTime = QDateTime::fromString(obj["low_moon"]["time"].toString(), Qt::ISODate),
        .low_moonElevation = obj["low_moon"]["elevation"].toString(),
        .low_moonDate = QDateTime::fromString(obj["low_moon"]["time"].toString(), Qt::ISODate),
        .moonsetTime = QDateTime::fromString(obj["moonset"]["time"].toString(), Qt::ISODate),
        .moonshadowElevation = obj["moonshadow"]["elevation"].toString(),
        .moonshadowAzimuth = obj["moonshadow"]["azimuth"].toString(),
        .moonshadowTime = QDateTime::fromString(obj["moonshadow"]["time"].toString(), Qt::ISODate),
    };
    return rise;
}

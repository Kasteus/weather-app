#pragma once

#include <QDateTime>

class QJsonObject;

class SunRise
{
public:
    static SunRise sunRiseParser(const QString &lon, const QString &lat, const QJsonObject &obj);

public:
    QString latitude;
    QString longitude;

    QDateTime sunsetTime;

    QString high_moonElevation;
    QDateTime high_moonTime;

    QString moonphaseValue;
    QDateTime moonphaseTime;

    QDateTime sunriseTime;

    QDateTime moonriseTime;

    QString solarnoonElevation;
    QDateTime solarnoonTime;

    QString solarmidnightElevation;
    QDateTime solarmidnightTime;

    QString moonpositionAzimuth;
    QString moonpositionPhase;
    QString moonpositionElevation;
    QString moonpositionRange;
    QDateTime moonpositionTime;

    QDateTime low_moonTime;
    QString low_moonElevation;
    QDateTime low_moonDate;

    QDateTime moonsetTime;

    QString moonshadowElevation;
    QString moonshadowAzimuth;
    QDateTime moonshadowTime;
};


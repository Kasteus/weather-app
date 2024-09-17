#pragma once

#include <QObject>

class QStringList;
class QJsonObject;

class WeatherLocalization
{
public:
    static WeatherLocalization localizationParser(const QJsonObject &obj);

public:
    QString place;
    QString licence;
    QString osm_type;
    QString osm_id;
    QStringList boundingbox;
    QString lat;
    QString lon;
    QString displayName;
    QString clas;
    QString type;
    QString importance;
    QString icon;
};

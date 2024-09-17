#pragma once

#include <QWidget>

class QIcon;
class QLabel;
class QSvgRenderer;

class WeatherDay: public QWidget
{
    Q_OBJECT

public:
    WeatherDay(QWidget *parent = nullptr);
    ~WeatherDay();

    void setData(const QByteArray &svgData, const QString &cloud, const QString &temp, const QString &wind);

public:
    QSvgRenderer *const m_svg;

    QLabel *const m_icon;
    QLabel *const m_cloud;
    QLabel *const m_temp;
    QLabel *const m_wind;
};


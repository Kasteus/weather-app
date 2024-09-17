#pragma once

#include <QWidget>
#include <QSettings>

class Unit;
class Network;
class Location;
class Apperance;
class QTabWidget;
class QPushButton;
class WeatherLocalization;

class WeatherProperties: public QWidget
{
    Q_OBJECT
public:
    WeatherProperties(QSettings &setting, QWidget *parent = nullptr);
    ~WeatherProperties();

    void writeSettings();
    void loadSettings();

signals:
    void updateInformation();

public:
    QPushButton *m_apply = nullptr;
    QPushButton *m_close = nullptr;

    QTabWidget *m_tabs     = nullptr;
    Location   *m_location = nullptr;
    Unit       *m_unit     = nullptr;
    Network    *m_network  = nullptr;
    Apperance *m_apperance = nullptr;

    std::vector<WeatherLocalization> m_locData;
    QSettings settings;
};

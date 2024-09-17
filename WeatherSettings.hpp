#pragma once

#include <QSettings>
#include <QSystemTrayIcon>

#include <WeatherDisplay.hpp>
#include <WeatherProperties.hpp>
#include <Network.hpp>

class QMenu;

class WeatherSettings: public QObject
{
    Q_OBJECT

public:
    WeatherSettings();

public:
    void setMenuActionEnabled(QMenu *menu, bool enable);

public:
    QSettings settings;

    QSystemTrayIcon tray;

    QMenu *trayMenu = nullptr;

    WeatherDisplay wds;
    QPointer<WeatherProperties> wd;

    Network net;
};

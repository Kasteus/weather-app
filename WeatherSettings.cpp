#include "WeatherSettings.hpp"

#include <QMessageBox>
#include <QApplication>
#include <QMenu>

#include <WeatherDayAdvance.hpp>


WeatherSettings::WeatherSettings()
{
    tray.setIcon(QIcon(__FILE__ "/../icons/cloud.svg"));
    tray.setVisible(true);

    trayMenu = new QMenu;
    auto propertiesWindow = trayMenu->addAction("&Properties");
    auto weatherWindow = trayMenu->addAction("&Weather");
    auto close = trayMenu->addAction("&Close");
    tray.setContextMenu(trayMenu);

//    connect(&wd, &WeatherProperties::refreshTimeChanged, &wds, &WeatherDisplay::setTimer);

    connect(&wds, &WeatherDisplay::updateTooltipInfo, [&](const QStringList &toolTipInfo){
    //        qDebug() << settings.value("Location/city").toString().isEmpty() << " " << settings.value("Location/city").toString();
        tray.setToolTip("City: " + settings.value("Location/city").toString() +
                        "\nCord: lat:" + toolTipInfo[0] + ", long:" + toolTipInfo[1] + ", alt: " + toolTipInfo[2] +
                        "\nCloudness: " + toolTipInfo[3] +
                        "\nTemp: " + toolTipInfo[4] +
                        "\nWind Speed: " + toolTipInfo[5] +  " " + toolTipInfo[6] +
                        "\nWind Direction:" + toolTipInfo[7] + " " + toolTipInfo[8] +
                        "\nPressure: " + toolTipInfo[9] +
                        "\nHumidity: " + toolTipInfo[10]
                        );
    });

    connect(propertiesWindow, &QAction::triggered, [=]{
        if (wd == nullptr)
        {
            wd = new WeatherProperties(settings);
            connect(wd, &WeatherProperties::updateInformation, &wds, &WeatherDisplay::loadSettings);
            wd->show();
        }
    });

    connect(weatherWindow, &QAction::triggered, &wds, &WeatherDisplay::show);

    connect(close,&QAction::triggered, [&] {
        QMessageBox msg(QMessageBox::Question, "Close the application", "Are sure want to close the application?", QMessageBox::No | QMessageBox::Yes);
        setMenuActionEnabled(trayMenu, false);
        auto ret = msg.exec();
        switch(ret)
        {
            case QMessageBox::No:
                msg.close();
                setMenuActionEnabled(trayMenu, true);
                break;
            case QMessageBox::Yes:
                msg.close();
                QApplication::quit();
                break;
        }
    });

    connect(&tray, &QSystemTrayIcon::activated, [&](QSystemTrayIcon::ActivationReason reason) {
        if (reason == QSystemTrayIcon::Trigger)
            wds.show();
    });
}

void WeatherSettings::setMenuActionEnabled(QMenu *menu, bool enable)
{
    for (auto &&action : menu->actions())
    {
        action->setEnabled(enable);
    }
}

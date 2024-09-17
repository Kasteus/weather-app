#include <Network.hpp>

#include <WeatherProperties.hpp>
#include <Location.hpp>

//#include <QCoreApplication>
#include <QDebug>

#include <QApplication>
#include <QSystemTrayIcon>
#include <QMenu>
//#include <QTextEdit>
#include <QTimer>
#include <QFile>

#include <WeatherDays.hpp>
#include <Network.hpp>
#include <WeatherDisplay.hpp>

#include <QSettings>
#include <WeatherDayAdvance.hpp>
#include <QMessageBox>

#include <WeatherSettings.hpp>

void setMenuActionEnabled(QMenu *menu, bool enable)
{
    for (auto &&action : menu->actions())
    {
        qDebug() << action;
        action->setEnabled(enable);
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Kasteus");
    QCoreApplication::setApplicationName("Weather");

    QSettings settings;

    qInstallMessageHandler([](QtMsgType t, const QMessageLogContext &c, const QString &m) {
        fprintf(stderr, "%s\n", qFormatLogMessage(t, c, m).toLocal8Bit().constData());
        fflush(stderr);
    });

    QApplication a(argc, argv);

    a.setQuitOnLastWindowClosed(false);

    WeatherSettings weather;

    return a.exec();
}

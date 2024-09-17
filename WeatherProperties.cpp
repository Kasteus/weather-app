#include "WeatherProperties.hpp"

#include <Unit.hpp>
#include <Network.hpp>
#include <Location.hpp>
#include <Apperance.hpp>

#include <QTabWidget>
#include <QGridLayout>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QDebug>
#include <QSettings>

#include <QPushButton>

WeatherProperties::WeatherProperties(QSettings &setting, QWidget *parent):
    QWidget(parent),
    settings(&setting)
{
    setAttribute(Qt::WA_DeleteOnClose, true);
    setWindowTitle("Weather - properties");
    m_tabs = new QTabWidget;
    m_tabs->addTab(m_location = new Location, "Location");
    m_tabs->addTab(m_unit = new Unit, "Unit");
    m_tabs->addTab(m_apperance = new Apperance, "Apperance");

    m_apply = new QPushButton("Apply");
    m_close = new QPushButton("Close");

    auto vLayout = new QVBoxLayout(this);
    auto hLayout = new QHBoxLayout(this);
    vLayout->addWidget(m_tabs);
    hLayout->addWidget(m_apply);
    hLayout->addWidget(m_close);
    vLayout->addLayout(hLayout);

    m_network = new Network(this);

    connect(m_network, &Network::localization,
            this, [=](const std::vector<WeatherLocalization> &vec) {
        m_locData = vec;
        QStringList list;
        list.reserve(vec.size());
        for (auto &i : vec)
        {
            list += i.displayName;
        }
        list.removeDuplicates();
        m_location->setCompleter(list);
    });

    connect(m_location, &Location::searchLocation,
             this, [=](const QString &text) {
        m_network->getLocalizationInfo(text);
    });

    connect(m_location, &Location::completerRow,
            this, [=](int index){
        if (index >= 0 && index < static_cast<int>(m_locData.size()))
        {
            m_location->setLocalizationData(m_locData[index].lat, m_locData[index].lon);
            m_location->setCompleter(QStringList());
        }
    });

    connect(m_apply, &QPushButton::clicked,[=]{
        writeSettings();
        emit updateInformation();
    });

    connect(m_close, &QPushButton::clicked,[=]{
        close();
    });

    loadSettings();
}
WeatherProperties::~WeatherProperties()
{}

void WeatherProperties::writeSettings()
{
    m_location->writeSettings();
    m_unit->writeSettings();
    m_apperance->writeSettings();
}

void WeatherProperties::loadSettings()
{
    m_location->loadSettings();
    m_unit->loadSettings();
    m_apperance->loadSettings();
}


#include "Unit.hpp"

#include <QLabel>
#include <QComboBox>
#include <QFormLayout>

#include <QSettings>

#include <QDebug>

Unit::Unit(QWidget *parent, QSettings *setting):
    QWidget(parent),
    settings(setting)
{
    initWindow();
}

Unit::~Unit()
{}

void Unit::initWindow()
{
    m_cbTemp    = new QComboBox;
    m_cbPres    = new QComboBox;
    m_cbWind    = new QComboBox;
    m_cbPrec    = new QComboBox;
    m_cbAlt     = new QComboBox;
    m_cbAppTemp = new QComboBox;

    m_cbTemp->addItems({
        "Celsius (\u2103)",
        "Farenheit (\u2109)",
        "Kelvin (K)",
    });

    m_cbPres->addItems({
        "Hectopascal (hPa)",
        "Inches of mercury (inHg)",
        "Pound-force per square inch (psi)",
        "Torr (mmHg)",
    });

    m_cbWind->addItems({
        "Kilometer per hour (km/h)",
        "Mile per hour (mph)",
        "Meter per second (m/s)",
        "Feet per second (ft/s)",
        "Knots (kt)",
    });

    m_cbPrec->addItems({
        "Milimeters (mm)",
        "Inches (in)"
    });

    m_cbAlt->addItems({
        "Meter (m)",
        "Feet (ft)",
    });

    m_cbAppTemp->addItems({
        "Heat index",
        "Wind Chill index",
    });

    auto layout = new QFormLayout(this);
    layout->addRow(tr("Temperature:"), m_cbTemp);
    layout->addRow(tr("Barometric pressure:"), m_cbPres);
    layout->addRow(tr("Wind speed:"), m_cbWind);
    layout->addRow(tr("Precipitations:"), m_cbPrec);
    layout->addRow(tr("Altitude:"), m_cbAlt);
    layout->addRow(tr("Apparent temperature:"), m_cbAppTemp);

    connect(m_cbTemp, qOverload<int>(&QComboBox::currentIndexChanged), [=](int idx){
        qDebug() << "temp1: " << idx;
        emit tempChanged(idx);
    });

    connect(m_cbPres, qOverload<int>(&QComboBox::currentIndexChanged), [=](int idx){
        emit pressureChanged(idx);
    });

    connect(m_cbWind, qOverload<int>(&QComboBox::currentIndexChanged), [=](int idx){
        emit windChanged(idx);
    });

    connect(m_cbPrec, qOverload<int>(&QComboBox::currentIndexChanged), [=](int idx){
        emit precChanged(idx);
    });

    connect(m_cbAlt, qOverload<int>(&QComboBox::currentIndexChanged), [=](int idx){
        emit altChanged(idx);
    });

    connect(m_cbAppTemp, qOverload<int>(&QComboBox::currentIndexChanged), [=](int idx){
        emit appTempChanged(idx);
    });
}

void Unit::loadSettings()
{
    qDebug() << "temp1: " << settings.value("Unit/temperature").toInt();
    int tempIdx, barIdx, windIdx, precIdx, altIdx, apperTempIdx;

    if (m_cbTemp && (tempIdx = settings.value("Unit/temperature").toInt()) < m_cbTemp->count())
    {
        if (tempIdx != m_cbTemp->currentIndex())
        {
            m_cbTemp->setCurrentIndex(tempIdx);
        }
        else
            emit tempChanged(tempIdx);
    }

    if (m_cbPres && (barIdx = settings.value("Unit/barometricPress").toInt()) < m_cbPres->count())
    {
        if (barIdx != m_cbPres->currentIndex())
        {
            m_cbPres->setCurrentIndex(barIdx);
        }
        else
            emit pressureChanged(barIdx);
    }

    if (m_cbWind && (windIdx = settings.value("Unit/windSpeed").toInt()) < m_cbWind->count())
    {
        if (windIdx != m_cbWind->currentIndex())
        {
            m_cbWind->setCurrentIndex(windIdx);
        }
        else
            emit windChanged(windIdx);
    }

    if (m_cbPrec && (precIdx = settings.value("Unit/precipitations").toInt()) < m_cbPrec->count())
    {
        if (precIdx != m_cbPrec->currentIndex())
        {
            m_cbPrec->setCurrentIndex(precIdx);
        }
        else
            emit precChanged(precIdx);
    }

    if (m_cbAlt && (altIdx = settings.value("Unit/altitude").toInt()) < m_cbAlt->count())
    {
        if (altIdx != m_cbAlt->currentIndex())
        {
            m_cbAlt->setCurrentIndex(altIdx);
        }
        else
            emit altChanged(altIdx);
    }

    if (m_cbAppTemp && (apperTempIdx = settings.value("Unit/apperentTemp").toInt()) < m_cbAppTemp->count())
    {
        if (apperTempIdx != m_cbAppTemp->currentIndex())
        {
            m_cbAppTemp->setCurrentIndex(apperTempIdx);
        }
        else
            emit appTempChanged(apperTempIdx);
    }
}

void Unit::writeSettings()
{
    settings.setValue("Unit/temperature", m_cbTemp->currentIndex());
    settings.setValue("Unit/barometricPress", m_cbPres->currentIndex());
    settings.setValue("Unit/windSpeed", m_cbWind->currentIndex());
    settings.setValue("Unit/precipitations", m_cbPrec->currentIndex());
    settings.setValue("Unit/altitude", m_cbAlt->currentIndex());
    settings.setValue("Unit/apperentTemp", m_cbAppTemp->currentIndex());
}

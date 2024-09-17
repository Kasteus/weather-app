#include "Apperance.hpp"

#include <QFormLayout>
#include <QComboBox>
#include <QSpinBox>

Apperance::Apperance(QWidget *parent, QSettings *setting):
    QWidget(parent),
    settings(setting)
{ 
    m_arrangementCb = new QComboBox;
    m_arrangementCb->addItem("Daytime/Day name");
    m_arrangementCb->addItem("Day name/Daytime");

    m_daysNumber = new QSpinBox;
    m_daysNumber->setRange(1, 6);

    m_time = new QSpinBox;
    m_time->setRange(10, 30);
    m_time->setSuffix(" min");

    auto layout = new QFormLayout(this);
    layout->addRow("Arrangement:", m_arrangementCb);
    layout->addRow("Displayed number of days", m_daysNumber);
    layout->addRow("Refresh rate", m_time);

    connect(m_arrangementCb, qOverload<int>(&QComboBox::currentIndexChanged), this, [=](int idx){
        emit layoutDirectionChanged(idx);
    });

    connect(m_daysNumber, qOverload<int>(&QSpinBox::valueChanged), this, [=](int value){
        emit numberOfDaysChanged(value);
    });

    connect(m_time, qOverload<int>(&QSpinBox::valueChanged), this, [=](int value){
        emit refreshTimeChanged(value);
    });
}

void Apperance::loadSettings()
{
    int arranIdx, numDaysIdx, time;

    if (m_arrangementCb && (arranIdx = settings.value("Apperance/arrangement").toInt()) < m_arrangementCb->count())
    {
        if (arranIdx != m_arrangementCb->currentIndex())
            m_arrangementCb->setCurrentIndex(arranIdx);
        else
            emit layoutDirectionChanged(arranIdx);
    }

    if (m_daysNumber && (numDaysIdx = settings.value("Apperance/numberDays").toInt()) <= m_daysNumber->maximum() && settings.value("Apperance/numberDays").toInt() >= m_daysNumber->minimum())
    {
        if (numDaysIdx != m_daysNumber->value())
            m_daysNumber->setValue(numDaysIdx);
        else
            emit numberOfDaysChanged(numDaysIdx);
    }

    if (m_time && (time = settings.value("Apperance/refreshTime").toInt()) <= m_time->maximum() && settings.value("Apperance/refreshTime").toInt() >= m_time->minimum())
    {
        if (time != m_time->value())
            m_time->setValue(time);
        else
            emit refreshTimeChanged(time);
    }
    //    qDebug() << m_arrangementCb->currentIndex() << " " << m_daysNumber->value() << " " << m_time->value() << " ";
}

void Apperance::writeSettings()
{
    settings.setValue("Apperance/arrangement", m_arrangementCb->currentIndex());
    settings.setValue("Apperance/numberDays", m_daysNumber->value());
    settings.setValue("Apperance/refreshTime", m_time->value());
}

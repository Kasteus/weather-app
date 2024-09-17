#include "Location.hpp"

#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QCompleter>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QStringListModel>
#include <QTimer>

#include <QDebug>

Location::Location(QWidget *parent, QSettings *setting):
    QWidget(parent),
    settings(setting)
{
    initWindow();
}

Location::~Location()
{}

void Location::initWindow()
{
    m_spinLat = new QDoubleSpinBox;
    m_spinLon = new QDoubleSpinBox;

    m_spinLat->setDecimals(6);
    m_spinLon->setDecimals(6);

    m_editCity = new QLineEdit;

    m_searchButton =  new QPushButton;
    m_searchButton->setToolTip(tr("Search localization"));

    m_model = new QStringListModel(this);
    m_complet = new QCompleter(m_model, this);
    m_complet->setCaseSensitivity(Qt::CaseInsensitive);

    m_editCity->setCompleter(m_complet);

    auto hLayout = new QHBoxLayout;
    auto hLayoutInfo = new QHBoxLayout;
    auto layout = new QFormLayout(this);
    auto m_info = new QLabel;
    auto m_infoIcon = new QLabel;

    hLayout->addWidget(m_editCity);
    hLayout->addWidget(m_searchButton);
    m_searchButton->setIcon(QIcon(__FILE__"/../icons/search.svg"));

    hLayoutInfo->addWidget(m_infoIcon);
    hLayoutInfo->addWidget(m_info);
    hLayoutInfo->addStretch(1);

    QPixmap pix("/home/dominik/Dokumenty/weather/icons/info.svg");
    m_infoIcon->setPixmap(pix);
    m_infoIcon->setScaledContents(true);
    m_info->setText(tr("To search for a location, the application uses <a href=\"https://nominatim.openstreetmap.org/\"> https://nominatim.openstreetmap.org</a> site."));
    m_info->setTextInteractionFlags(Qt::TextBrowserInteraction);
    m_info->setOpenExternalLinks(true);

    layout->addRow(tr("Location name:"), hLayout);
    layout->addRow(tr("Latitude:"), m_spinLat);
    layout->addRow(tr("Longitude:"), m_spinLon);
    layout->addRow(hLayoutInfo);

    //TODO add info label

    connect(m_spinLat, qOverload<double>(&QDoubleSpinBox::valueChanged), [=](double value){
        bool clearText = false;
        if (!m_editCity->text().isEmpty() && QString::number(tempLat, 'g', 6) != QString::number(value, 'g', 6))
        {
            m_editCity->setText("Custom");
            clearText = true;
        }
        emit latChanged(value, clearText);
    });

    connect(m_spinLon, qOverload<double>(&QDoubleSpinBox::valueChanged), [=](double value){
        bool clearText = false;
        if (!m_editCity->text().isEmpty() && QString::number(tempLon, 'g', 6) != QString::number(value, 'g', 6))
        {
            m_editCity->setText("Custom");
            clearText = true;
        }
        emit lonChanged(value, clearText);
    });

    connect(m_searchButton, &QPushButton::clicked, [=](){
        emit searchLocation(m_editCity->text());
        m_searchButton->setDisabled(true);
        m_editCity->setFocus();
        QTimer::singleShot(1500,[=]{
            m_searchButton->setEnabled(true);
        });
    });

    connect(m_complet, qOverload<const QModelIndex &>(&QCompleter::activated), [=](const QModelIndex &index){
        emit completerRow(index.row());
    });

}

void Location::setCompleter(const QStringList &list)
{
    m_model->setStringList(list);
    if (m_editCity->hasFocus())
        m_complet->complete();
}

void Location::setLocalizationData(const QString &lat, const QString &lon)
{
    tempLat = QString::number(lat.toDouble(), 'g', 6).toDouble();
    tempLon = QString::number(lon.toDouble(), 'g', 6).toDouble();

    m_spinLat->setValue(lat.toDouble());
    m_spinLon->setValue(lon.toDouble());
}

void Location::setSearchEnabled()
{
    m_searchButton->setDisabled(false);
}

void Location::loadSettings()
{
    QString cityName = settings.value("Location/city").toString();

    const double lat = settings.value("Location/lat").toDouble();
    const double lon = settings.value("Location/lon").toDouble();

    if (m_spinLat && lat <= m_spinLat->maximum() && lat >= m_spinLat->minimum())
    {
        tempLat = lat;
        m_spinLat->setValue(lat);
    }

    if (m_spinLon && lon <= m_spinLon->maximum() && lon >= m_spinLon->minimum())
    {
        tempLon = lon;
        m_spinLon->setValue(lon);
    }

    QTimer::singleShot(100,this,[=]{
        emit latChanged(m_spinLat->value(), false);
        emit lonChanged(m_spinLon->value(), false);
        m_editCity->setText(cityName);
    });
}

void Location::writeSettings()
{
    settings.setValue("Location/city", m_editCity->text());
    settings.setValue("Location/lat", m_spinLat->value());
    settings.setValue("Location/lon", m_spinLon->value());
}

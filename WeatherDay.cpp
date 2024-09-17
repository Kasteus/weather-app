#include "WeatherDay.hpp"

#include <QIcon>
#include <QLabel>
#include <QVBoxLayout>
#include <QSvgRenderer>

#include <QPixmap>
#include <QPainter>

WeatherDay::WeatherDay(QWidget *parent)
    : QWidget(parent)
    , m_svg(new QSvgRenderer(this))
    , m_icon(new QLabel)
    , m_cloud(new QLabel)
    , m_temp(new QLabel)
    , m_wind(new QLabel)
{
    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_icon, 0, Qt::AlignCenter);
    layout->addWidget(m_cloud, 0, Qt::AlignCenter);
    layout->addWidget(m_temp, 0, Qt::AlignCenter);
    layout->addWidget(m_wind, 0, Qt::AlignCenter);
}
WeatherDay::~WeatherDay()
{}

void WeatherDay::setData(const QByteArray &svgData, const QString &cloud, const QString &temp, const QString &wind)
{
    m_svg->load(svgData);

    QPixmap pm(100, 100);
    pm.fill(Qt::transparent);
    QPainter painter(&pm);
    m_svg->render(&painter, pm.rect());

    m_icon->setPixmap(pm);
    m_cloud->setText(cloud);
    m_temp->setText(temp);
    m_wind->setText(wind);

    auto size = sizeHint();
    setMinimumSize(size.width() + 100, size.height());
}

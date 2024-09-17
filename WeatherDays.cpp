#include "WeatherDays.hpp"

#include <SunRise.hpp>
#include <WeatherDay.hpp>
#include <VerticalLabel.hpp>
#include <WeatherData.hpp>
#include <Unit.hpp>

#include <QStyle>
#include <QLabel>
#include <QScrollBar>
#include <QGridLayout>

#include <QFile>
#include <QLocale>
#include <QDebug>
#include <QCoreApplication>

using namespace std;

WeatherDays::WeatherDays(QWidget *parent)
    : QScrollArea(parent)
{
    readIcons();

    initWindow();
    setPalette(Qt::white);
}
WeatherDays::~WeatherDays()
{}

void WeatherDays::initWindow()
{
    setWidgetResizable(true);

    m_daysName = getDayNames();

    m_daysHourTime.append({
        tr("Morning"),
        tr("Afternoon"),
        tr("Evening"),
        tr("Night"),
    });

    m_layoutDirection = 0;
    setNumberOfDays(6);
}
const QStringList WeatherDays::getDayNames() const
{
    QLocale locale(QLocale::English);
    auto dayNumber = QDate::currentDate().dayOfWeek();

    const QStringList daysName = {
        tr("Today"),
        tr("Tomorrow"),
        dayNumber + 2 > 7 ? locale.dayName(dayNumber + 2 - 7) : locale.dayName(dayNumber + 2),
        dayNumber + 3 > 7 ? locale.dayName(dayNumber + 3 - 7) : locale.dayName(dayNumber + 3),
        dayNumber + 4 > 7 ? locale.dayName(dayNumber + 4 - 7) : locale.dayName(dayNumber + 4),
        dayNumber + 5 > 7 ? locale.dayName(dayNumber + 5 - 7) : locale.dayName(dayNumber + 5),
    };
    return daysName;
}

void WeatherDays::readIcons()
{
    const QString iconsPath = QCoreApplication::applicationDirPath() + "/icons";
    for (int i = 0; i < 51; ++i)
    {
        auto readIcon = [&](const QString &subdir, vector<QByteArray> &arr) {
            QFile file(QString("%1/%2/%3.svg").arg(iconsPath, subdir).arg(i));
            if (file.open(QIODevice::ReadOnly))
                arr.push_back(file.readAll());
            else
                arr.push_back(QByteArray());
        };
        readIcon("night", m_iconNight);
        readIcon("day", m_iconDay);
    }
}
void WeatherDays::setWeatherData()
{
    if (m_daysInfo.empty() || m_daysInfo.size() < m_days * 4)
        return;

    for (uint32_t i = 0; i < m_days * 4; ++i)
    {
        QString tempVal, windVal;

        switch (m_tempUnit)
        {
            case Unit::Temperature::Celsius:
                tempVal = m_daysInfo[i].temp + "(\u2103)";
                break;
            case Unit::Temperature::Farenheit:
                tempVal = QString::number((m_daysInfo[i].temp.toDouble() * 1.8) + 32, 'G', 3) + "(\u2109)";
                break;
            case Unit::Temperature::Kelvin:
                tempVal = QString::number(m_daysInfo[i].temp.toDouble() + 273.15, 'G', 3) + "(K)";
                break;
        }

        switch (m_windUnit)
        {
            case Unit::Wind::Km_h:
                windVal = QString::number(m_daysInfo[i].windSpeed.toDouble() * 3.6, 'G', 3) + "(km/h)";
                break;
            case Unit::Wind::Mp_h:
                windVal = QString::number(m_daysInfo[i].windSpeed.toDouble() * 2.24, 'G', 3) + "(mph)";
                break;
            case Unit::Wind::M_s:
                windVal = QString::number(m_daysInfo[i].windSpeed.toDouble(), 'G', 3) + "(m/s)";
                break;
            case Unit::Wind::Ft_s:
                windVal = QString::number(m_daysInfo[i].windSpeed.toDouble() * 3.280839895013, 'G', 3) + "(ft/s)";
                break;
            case Unit::Wind::Kt:
                windVal = QString::number(m_daysInfo[i].windSpeed.toDouble() * 1.943844492441, 'G', 3) + "(Kt)";
                break;
        }

        m_daysData[i]->setData(
            m_daysInfo[i].sybmol
                ? m_night
                    ? m_iconNight[m_daysInfo[i].sybmol]
                    : m_iconDay[m_daysInfo[i].sybmol]
                : QByteArray(),
            m_daysInfo[i].cloudness,
            m_daysInfo[i].temp.isEmpty() ? "" : tempVal,
            m_daysInfo[i].windSpeed.isEmpty() ? "" : windVal
        );
    }
}
void WeatherDays::setNumberOfDays(int i)
{
    m_days = i;

    if (m_layoutDirection)
        verticalLayout();
    else
        horizontalLayout();
}

void WeatherDays::verticalLayout()
{
    auto layout = createLayout(1);

    for (auto i = 0; i < m_daysHourTime.count(); ++i)
    {
        auto container = new QWidget;

        auto l = new QGridLayout(container);
        l->addWidget(new QLabel(m_daysHourTime.at(i)), 0, 0, Qt::AlignHCenter);

        container->setAutoFillBackground(true);
        container->setPalette(Qt::darkGray);
        layout->addWidget(container, 1, i + 2);
    }

    for (uint32_t i = 0; i < m_days * 4; ++i)
    {
        int x = (i / 4);
        int y = (i % 4);

        if (y == 0 && m_daysName.count() > x)
        {
            auto container = new QWidget;

            auto l = new QGridLayout(container);
            l->addWidget(new VerticalLabel(m_daysName.at(x)), 0, 0, Qt::AlignCenter);

            container->setAutoFillBackground(true);
            container->setPalette(Qt::darkGray);
            layout->addWidget(container, x + 2, 1);
        }

        m_daysData[i]->setPalette((x & 1) ? Qt::lightGray : Qt::gray);
        layout->addWidget(m_daysData[i], x + 2, y + 2);
    }

    layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 0, 0);
    layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), layout->rowCount(), layout->columnCount());

    setWeatherData();
}

void WeatherDays::horizontalLayout()
{
    auto layout = createLayout(0);

    for (auto i = 0; i < m_daysHourTime.count(); ++i)
    {
        auto container = new QWidget;
        auto l = new QGridLayout(container);

        l->addWidget(new VerticalLabel(m_daysHourTime.at(i)), 0, 0, Qt::AlignCenter);

        container->setAutoFillBackground(true);
        container->setPalette(Qt::darkGray);
        layout->addWidget(container, i + 2, 1);
    }

    for (uint32_t i = 0; i < m_days * 4; ++i)
    {
        int y = (i / 4);
        int x = (i % 4);

        if (x == 0 && m_daysName.count() > y)
        {
            auto container = new QWidget;

            auto l = new QGridLayout(container);
            l->addWidget(new QLabel(m_daysName.at(y)), 0, 0, Qt::AlignHCenter);

            container->setAutoFillBackground(true);
            container->setPalette(Qt::darkGray);
            layout->addWidget(container, 1, y + 2);
        }

        m_daysData[i]->setPalette((y & 1) ? Qt::lightGray : Qt::gray);
        layout->addWidget(m_daysData[i], x + 2, y + 2);
    }

    layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 0, 0);
    layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), layout->rowCount(), 0);
    layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), layout->rowCount(), layout->columnCount());

    setWeatherData();
}

void WeatherDays::setWeatherInfo(const std::vector<WeatherData> &data)
{
    m_daysInfo.clear();
    vector<QDateTime> dates;
    dates.reserve(m_days * 4 + 1);
    for (uint32_t i = 0;; ++i)
    {
        auto time = QDateTime::currentDateTimeUtc().addDays(i);

        time.setTime(QTime(0, 0));
        dates.push_back(time);

        if (i == m_days)
            break;

        time.setTime(QTime(6, 0));
        dates.push_back(time);

        time.setTime(QTime(12, 0));
        dates.push_back(time);

        time.setTime(QTime(18, 0));
        dates.push_back(time);
    }
    Q_ASSERT(dates.size() == dates.capacity());

    for (auto &&weatherItem : data)
    {
        for (size_t i = 1; i < dates.size(); ++i)
        {
            const auto &date = dates[i - 1];
            if (weatherItem.timeFrom != date || weatherItem.timeTo != dates[i])
                continue;

            DaysInformation day;
            bool found = false;

            for (auto &&weatherElement : data)
            {
                if (weatherElement.timeFrom == date && weatherElement.timeTo == date)
                {
                    day.temp =  QString::number(weatherElement.temperatureValue);
                    day.windSpeed = QString::number(weatherElement.windSpeedMps);
                    found = true;
                    break;
                }
            }

            day.dateFrom = weatherItem.timeFrom;
            day.dateTo = weatherItem.timeTo;

            if (found || m_daysInfo.empty())
            {
                day.cloudness = weatherItem.symbol;
                day.sybmol = weatherItem.symbolID;
                if (!found)
                {
                    day.temp = QString::number(data[0].temperatureValue);
                    day.windSpeed = QString::number(data[0].windSpeedMps);
                }
            }
            // qDebug() << weatherItem.timeFrom << weatherItem.timeTo << weatherItem.symbol;
            m_daysInfo.push_back(day);
        }
    }

    auto dateTime = QDateTime::currentDateTimeUtc();
    for (auto &&weatherItem : data)
    {
        if (!m_daysInfo[0].cloudness.isEmpty())
            break;

        if (!weatherItem.symbol.isEmpty() && weatherItem.symbolID > 0 && weatherItem.timeFrom <= dateTime && weatherItem.timeTo >= dateTime)
        {
            m_daysInfo[0].cloudness = weatherItem.symbol;
            m_daysInfo[0].sybmol = weatherItem.symbolID;
            break;
        }
    }

    for (size_t i = 0; i < dates.size(); ++i)
    {
        bool found = false;
        for (size_t j = 0; j < m_daysInfo.size(); ++j)
        {
            if (j + 1 < dates.size() && dates[i] == m_daysInfo[j].dateFrom && dates[j + 1] == m_daysInfo[j].dateTo)
            {
                found = true;
                break;
            }
        }
        if (!found && i + 1 < dates.size())
            m_daysInfo.insert(m_daysInfo.begin() + i, {dates[i], dates[i + 1], "", "", "", 0});
    }
    setWeatherData();
}

void WeatherDays::setSunriseInfo(const std::vector<SunRise> &data)
{
    auto time = QDateTime::currentDateTimeUtc();
    m_night = (data[0].sunriseTime >= time || time >= data[0].sunsetTime);
    setWeatherData();
}

void WeatherDays::setTempUnit(int idx)
{
    m_tempUnit = idx;
    setWeatherData();
}

void WeatherDays::setWindUnit(int idx)
{
    m_windUnit = idx;
    setWeatherData();
}

QGridLayout *WeatherDays::createLayout(int direction)
{
    m_daysData.clear();

    delete widget();
    setWidget(new QWidget);

    for (uint32_t i = 0; i < m_days * 4; ++i)
    {
        auto day = new WeatherDay;
        day->setAutoFillBackground(true);

        m_daysData.push_back(day);
    }

    auto w = new QWidget;
    w->setAutoFillBackground(true);
    w->setPalette(Qt::darkGray);

    auto layout = new QGridLayout(widget());
    layout->setSpacing(0);
    layout->addWidget(w, 1, 1);

    m_layoutDirection = direction;

    return layout;
}

QSize WeatherDays::sizeHint() const
{
    const int scrollBarWidth = verticalScrollBar()->style()->pixelMetric(QStyle::PM_ScrollBarSliderMin, nullptr, verticalScrollBar());
    const int scrollBarHeight = horizontalScrollBar()->style()->pixelMetric(QStyle::PM_ScrollBarSliderMin, nullptr, horizontalScrollBar());
    return widget()->sizeHint() + QSize(scrollBarWidth, scrollBarHeight);
}

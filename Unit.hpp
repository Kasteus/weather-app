#pragma once

#include <QWidget>
#include <QSettings>

class QComboBox;

class Unit: public QWidget
{
    Q_OBJECT

public:
    enum Temperature
    {
        Celsius     = 0,
        Farenheit   = 1,
        Kelvin      = 2,
    };

    enum Pressure
    {
        Hectopascal = 0,
        InchMercury = 1,
        PoundForce  = 2,
        Torr        = 3,
    };

    enum Wind
    {
        Km_h = 0,
        Mp_h = 1,
        M_s  = 2,
        Ft_s = 3,
        Kt   = 4,
    };

    enum Precipiation
    {
        Milimeters = 0,
        Inches     = 1,
    };

    enum Altitude
    {
        Meter = 0,
        Feet  = 1,
    };

    enum ApperentTemp
    {
        Heat  = 0,
        Chill = 1,
    };

public:
    Unit(QWidget *parent = nullptr, QSettings *setting = nullptr);
    ~Unit();

    void initWindow();
    void loadSettings();
    void writeSettings();

signals:
    void tempChanged(int idx);
    void pressureChanged(int idx);
    void windChanged(int idx);
    void precChanged(int idx);
    void altChanged(int idx);
    void appTempChanged(int idx);

public:
    QSettings settings;

    QComboBox *m_cbTemp    = nullptr;
    QComboBox *m_cbPres    = nullptr;
    QComboBox *m_cbWind    = nullptr;
    QComboBox *m_cbPrec    = nullptr;
    QComboBox *m_cbAlt     = nullptr;
    QComboBox *m_cbAppTemp = nullptr;
};

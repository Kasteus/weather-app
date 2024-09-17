#pragma once

#include <QWidget>
#include <QSettings>

class QLabel;
class QLineEdit;
class QCompleter;
class QPushButton;
class QDoubleSpinBox;
class QStringListModel;

class Location: public QWidget
{
    Q_OBJECT

public:
    Location(QWidget *parent = nullptr, QSettings *setting = nullptr);
    ~Location();

    void initWindow();
    void setCompleter(const QStringList &list);
    void setLocalizationData(const QString &lat, const QString &lon);
    void setSearchEnabled();

    void loadSettings();
    void writeSettings();

signals:
    void latChanged(double value, bool clearText);
    void lonChanged(double value, bool clearText);
    void altChanged(int value);
    void cityChanged(const QString &text);
    void completerRow(int index);
    void searchLocation(const QString &text);

public:
    QSettings settings;

    QDoubleSpinBox *m_spinLat = nullptr;
    QDoubleSpinBox *m_spinLon = nullptr;

    QLineEdit *m_editCity = nullptr;

    QCompleter *m_complet  = nullptr;

    QStringListModel *m_model = nullptr;

    QLabel *m_info = nullptr;

    QPushButton *m_searchButton = nullptr;
    double tempLon, tempLat;
};

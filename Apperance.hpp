#pragma once

#include <QWidget>
#include <QSettings>

class QComboBox;
class QSpinBox;

class Apperance: public QWidget
{
    Q_OBJECT
public:
    Apperance(QWidget *parent = nullptr, QSettings *setting = nullptr);

    void loadSettings();
    void writeSettings();

signals:
    void layoutDirectionChanged(int idx);
    void numberOfDaysChanged(int value);
    void refreshTimeChanged(int value);

public:
    QSettings settings;
    QComboBox *m_arrangementCb = nullptr;
    QSpinBox *m_daysNumber = nullptr;
    QSpinBox *m_time = nullptr;
};


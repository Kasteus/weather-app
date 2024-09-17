#pragma once

#include <QWidget>

class VerticalLabel : public QWidget
{
    Q_OBJECT

public:
    VerticalLabel(const QString &text = QString(), QWidget *parent = nullptr);
    ~VerticalLabel()
    {}

    void setText(const QString &text);
    QString text() const;

protected:
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    void paintEvent(QPaintEvent *e) override;

    bool event(QEvent *event) override;

private:
    void obtainSizeHint();

private:
    QString m_text;
    QSize m_sizeHint;
    int m_ascent = 0;
};

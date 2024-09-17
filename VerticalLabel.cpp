#include "VerticalLabel.hpp"

#include <QEvent>
#include <QPainter>

VerticalLabel::VerticalLabel(const QString &text, QWidget *parent)
    : QWidget(parent)
    , m_text(text)
{
    obtainSizeHint();
}

void VerticalLabel::setText(const QString &text)
{
    if (m_text == text)
        return;
    m_text = text;
    obtainSizeHint();
    update();
}

QString VerticalLabel::text() const
{
    return m_text;
}

QSize VerticalLabel::minimumSizeHint() const
{
    return m_sizeHint;
}

QSize VerticalLabel::sizeHint() const
{
    return m_sizeHint;
}

void VerticalLabel::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    QPainter p(this);
    p.rotate(-90.0);
    p.drawText(-m_sizeHint.height(), m_ascent, m_text);
}

bool VerticalLabel::event(QEvent *event)
{
    switch (event->type())
    {
        case QEvent::FontChange:
            obtainSizeHint();
            break;
        default:
            break;
    }
    return QWidget::event(event);
}

void VerticalLabel::obtainSizeHint()
{
    const QFontMetrics fm(font());
    const QSize newSizeHint(fm.height(), fm.horizontalAdvance(m_text));
    if (newSizeHint != m_sizeHint)
    {
        m_sizeHint = newSizeHint;
        m_ascent = fm.ascent();
        updateGeometry();
    }
}

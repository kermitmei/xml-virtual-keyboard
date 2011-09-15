#include "KbItem.h"


KbItem::KbItem():QGraphicsItem()
{
    setAcceptedMouseButtons(Qt::LeftButton);
}

KbItem::~KbItem()
{
    
}

QRectF KbItem::boundingRect() const
{
    return QRectF(0,0,m_width, m_height);
}

void KbItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(QBrush(QColor(85,85,85)));
    painter->drawRect(0,0,m_width, m_height);
    painter->setFont(QFont("Times", 18, QFont::Bold));
    painter->drawText(0,0, m_width, m_height, Qt::AlignCenter, m_text);
}

#include "KbKey.h"


KbKey::KbKey():QGraphicsItem(), m_pixmap(0)
{
    setAcceptedMouseButtons(Qt::LeftButton);
}

KbKey::~KbKey()
{
    if(m_pixmap)
	delete m_pixmap;
}

QRectF KbKey::boundingRect() const
{
    return QRectF(0,0,m_width, m_height);
}

void KbKey::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(m_pixmap != 0)
    {
	painter->drawPixmap(0,0, m_width, m_height, *m_pixmap);
    }
    else
    {
	painter->setBrush(QBrush(QColor(85,85,85)));
    }
    //    painter->drawRect(0,0,m_width, m_height);
    painter->setFont(QFont("Times", 18, QFont::Bold));
    painter->drawText(0,0, m_width, m_height, Qt::AlignCenter, m_text);
}


void KbKey::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    //    QGraphicsItem::mousePressEvent(event);
}

void KbKey::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
}

#include "KbItem.h"


KbItem::KbItem():QGraphicsItem(), m_pixmap(0)
{
    setAcceptedMouseButtons(Qt::LeftButton);
}

KbItem::~KbItem()
{
    if(m_pixmap)
	delete m_pixmap;
}

QRectF KbItem::boundingRect() const
{
    return QRectF(0,0,m_width, m_height);
}

void KbItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
    painter->drawRect(0,0,m_width, m_height);
    painter->setFont(QFont("Times", 18, QFont::Bold));
    painter->drawText(0,0, m_width, m_height, Qt::AlignCenter, m_text);
}


void KbItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("mousePressEvent");
    /*    KbView* view = dynamic_cast<KbView *>(event->widget());
    if( view != 0)
	view->setSceneNum(1);
    else
	qDebug("error mousepressevent");

	qDebug("mousePressEvent1");*/
    QGraphicsItem::mousePressEvent(event);
}

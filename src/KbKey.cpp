#include "KbKey.h"
#include "KbManager.h"

KbKey::KbKey()
 : m_pixmap(0), m_pixmapPressed(0),
   m_press(false)
{
    setAcceptedMouseButtons(Qt::LeftButton);
}

KbKey::~KbKey()
{
    //
}

QRectF KbKey::boundingRect() const
{
    return QRectF(0,0,m_width, m_height);
}

void KbKey::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::NoPen);
    if(m_pixmap != 0)
    {
	if(m_press == true)
	{
	    //painter->setBrush(QBrush(QColor(255,246,143)));
	    //painter->drawRect(0,0,m_width, m_height);
	    painter->setFont(QFont("Times", 11, QFont::Normal));
	    painter->drawPixmap(0,0, m_width, m_height, *m_pixmapPressed);
	}
	else
	{
	    painter->setFont(QFont("Times", 14, QFont::Normal));
	    painter->drawPixmap(0,0, m_width, m_height, *m_pixmap);
	}
    }
    else
    {
	painter->setBrush(QBrush(QColor(85,85,85)));
    }
    painter->setBrush(QBrush(QColor(255,246,143)));
    painter->setPen(Qt::black);
    painter->drawText(0,0, m_width, m_height, Qt::AlignCenter, m_text);
}

void KbKey::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    m_press = true;
#ifndef X86_LINUX
    if(m_keycode >= 0)
	send_a_key(m_keycode);
#endif
    update();
}

void KbKey::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_press = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void KbKey::setBackground(QString background)
{
    m_background = background;
    m_pixmap = const_cast<QPixmap *>(g_KbManager->getPixmap(background));
    m_pixmap = const_cast<QPixmap *>(g_KbManager->getPixmap(background, m_pixmap));
    background.replace(".png", "_pressed.png");
    m_pixmapPressed = const_cast<QPixmap *>(g_KbManager->getPixmap(background));
    m_pixmapPressed = const_cast<QPixmap *>(g_KbManager->getPixmap(background,m_pixmapPressed));
    
}

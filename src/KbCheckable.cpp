#include "KbCheckable.h"
#include "KbManager.h"

KbCheckable::KbCheckable()
    :m_pixmap(0), m_pixmapPressed(0),
     m_press(false)
{
    setAcceptedMouseButtons(Qt::LeftButton);
}

KbCheckable::~KbCheckable()
{
    //
}

QRectF KbCheckable::boundingRect() const
{
    return QRectF(0,0,m_width, m_height);
}

void KbCheckable::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

void KbCheckable::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    if(m_checkable == 0)
    {
	m_press = true;
#ifdef _X86_UINPUT_
	send_press_key(m_keycode);
#endif //_X86_UINPUT_
    }
    else if(m_checkable == 1)
    {
	m_press = false;
#ifdef _X86_UINPUT_
	send_release_key(m_keycode);
#endif //_X86_UINPUT_
    }
    m_checkable ++ ;
    update();
}

void KbCheckable::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_checkable == 2)
    {
	m_checkable = 0;
    }
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void KbCheckable::setBackground(QString background)
{
    m_background = background;
    m_pixmap = const_cast<QPixmap *>(g_KbManager->getPixmap(background));
    background.replace(".png", "_pressed.png");
    m_pixmapPressed = const_cast<QPixmap *>(g_KbManager->getPixmap(background));
    
}

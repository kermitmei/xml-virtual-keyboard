#include "KbView.h"
#include "KbItem.h"

KbView::KbView(QWidget *parent ) : QGraphicsView(parent),m_count(0)
{
    setWindowFlags(Qt::FramelessWindowHint);
}

void KbView::mousePressEvent(QMouseEvent *event)
{
    KbItem *item = dynamic_cast<KbItem *>(itemAt(event->pos()));
    if( item != 0 && item->keycode() <= 0)
    {
	if(item->text() == "next")
	{
	    m_count++;
	    setSceneNum(m_count);
	    
	}
	else if(item->text() == "up")
	{
	    m_count --;
	    setSceneNum(m_count);
	}
    }
    QGraphicsView::mousePressEvent(event);
}

#include "KbView.h"
#include "KbItem.h"


KbView::KbView(QWidget *parent ) : QGraphicsView(parent),m_count(0), m_moveView(false), m_oldGlobalPos(0,0)
{
    setWindowFlags(Qt::FramelessWindowHint);
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()),
	    this, SLOT(moveView()));
}

void KbView::mousePressEvent(QMouseEvent *event)
{
    m_timer->start(1000);
    m_oldGlobalPos = event->globalPos();
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

void KbView::mouseReleaseEvent(QMouseEvent *event)
{
    setCursor(Qt::ArrowCursor);
    m_timer->stop();
    m_moveView = false;
    QGraphicsView::mouseReleaseEvent(event);
}

void KbView::mouseMoveEvent(QMouseEvent *event)
{
    if(m_moveView == false && (event->globalX() < this->x() ||
			       event->globalY() < this->y() ||
			       event->globalX() > this->x() + this->width() ||
			       event->globalY() > this->y() + this->height()))
    {
	m_timer->stop();
    }
    else if(m_moveView == true )
    {
	int off_x = event->globalX() - m_oldGlobalPos.x();
	int off_y = event->globalY() - m_oldGlobalPos.y();
	m_oldGlobalPos.setX(event->globalX());
	m_oldGlobalPos.setY(event->globalY());
	move(this->x() + off_x, this->y() + off_y);
    }
    else
    {
	m_moveView = false;
    }
    QGraphicsView::mouseMoveEvent(event);
}

void KbView::moveView()
{
    m_moveView = true;
    setCursor(Qt::SizeAllCursor);
    m_timer->stop();
}

#include "KbView.h"

KbView::KbView(QWidget *parent ) : QGraphicsView(parent),m_count(0), m_moveView(false), m_oldGlobalPos(0,0)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowFlags(Qt::ToolTip);
    setAttribute(Qt::WA_DeleteOnClose);
    m_timer = new QTimer(this);
    setStyleSheet("border-image: url(./pics/shabu.png);");
    connect(m_timer, SIGNAL(timeout()),
	    this, SLOT(moveView()));
}

KbView::~KbView()
{
    foreach(KbPage *page, m_pageList)
    {
	foreach(QGraphicsItem *item , page->items())
	{
	    KbKey *key = dynamic_cast<KbKey *>(item);
	    if(key != 0)
	    {
		delete key;
	    }
	}
    }
}

void KbView::mousePressEvent(QMouseEvent *event)
{
    m_timer->start(1000);
    m_oldGlobalPos = event->globalPos();
    KbKey *key = dynamic_cast<KbKey *>(itemAt(event->pos()));
    if(key != 0 && key->keycode() < 0)
    {
	if(key->keycode() == -1)
	{
	    m_count++;
	    setSceneNum(m_count);
	}
	else if(key->keycode() == -2)
	{
	    m_count --;
	    setSceneNum(m_count);
	}
	return ;
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

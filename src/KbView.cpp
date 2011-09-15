#include "KbView.h"


KbView::KbView(QWidget *parent ) : QGraphicsView(parent),m_count(1)
{
    setWindowFlags(Qt::FramelessWindowHint);
}

void KbView::mousePressEvent(QMouseEvent *event)
{
    qDebug("KbView::mousePressEvent");
    if(m_count <= m_sceneList.count() -1)
    {
	setSceneNum(m_count);
	m_count++;
    }
    else
    {
	m_count = 0;
	setSceneNum(m_count);
	m_count++;
    }
    QGraphicsView::mousePressEvent(event);
}

#include "KbView.h"
#include "KbItem.h"

KbView::KbView(QWidget *parent ) : QGraphicsView(parent),m_count(1)
{
    setWindowFlags(Qt::FramelessWindowHint);
}

void KbView::mousePressEvent(QMouseEvent *event)
{
    qDebug("KbView::mousePressEvent");
    KbItem *item = dynamic_cast<KbItem *>(itemAt(event->pos()));
    qDebug("keycode = %d", item->keycode());
    qDebug("count = %d", m_sceneList.count());
    if( item != 0 && item->keycode() <= m_sceneList.count() -1)
    {
	qDebug("scene");
	setSceneNum(item->keycode());
    }

    QGraphicsView::mousePressEvent(event);
}

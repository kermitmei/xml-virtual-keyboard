#include "DropView.h"
#include "MyScene.h"
#include <QMimeData>

DropView::DropView(QWidget *parent) : QGraphicsView(parent)
{
    //no data;
    MyScene* scene = new MyScene;
    scene->setSceneRect(0,0,width(),height());
    //    setWindowFlags(Qt::ToolTip);
    //    setScene(scene);
    textEdit = new QTextEdit(this);
    
    textEdit->setAcceptDrops(true);
    //    setMouseTracking(true);
    setAcceptDrops(true);
}

void DropView::dropEvent(QDropEvent *event)
{
    qDebug("DropView::dropEvent()");
    textEdit->setText(event->mimeData()->text());
    QGraphicsView::dropEvent(event);
}

void DropView::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug("DropView::dragEnterEvent()");
    if(event->mimeData()->hasText())
    {
	event->acceptProposedAction();
    }
    QGraphicsView::dragEnterEvent(event);
}

void DropView::dragLeaveEvent(QDragLeaveEvent *event)
{
    qDebug("DropView::dragLeaveEvent");
    QGraphicsView::dragLeaveEvent(event);
}

void DropView::dragMoveEvent(QDragMoveEvent *event)
{
    qDebug("DropView::dragMoveEvent");
    QGraphicsView::dragMoveEvent(event);
}

void DropView::mouseMoveEvent(QMouseEvent *event)
{
    //    qDebug("x= %d, y= %d", event->x(), event->y());
    QGraphicsView::mouseMoveEvent(event);
}

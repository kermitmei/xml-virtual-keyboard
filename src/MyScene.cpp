#include "MyScene.h"
#include "MyItem.h"
#include <QVariant>

MyScene::MyScene() : QGraphicsScene()
{
    //no data;
}

void MyScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    //    qDebug("myScene dragEnterEvent");
    event->acceptProposedAction();
    QGraphicsScene::dragEnterEvent(event);
}

void MyScene::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    //    qDebug("myScene dragLeaveEvent");
    QGraphicsScene::dragLeaveEvent(event);
}

void MyScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    /*    qDebug("scene x = %s ,y = %s", 
	   QVariant(event->scenePos().x()).toString().toUtf8().constData(),
	   QVariant(event->scenePos().y()).toString().toUtf8().constData());
    qDebug("screen x = %d, y = %d", event->screenPos().x(), event->screenPos().y());
    if(mouseGrabberItem() == 0)
    {
	qDebug("0000");
    }
    if(focusItem() == 0)
    {
	qDebug("1111");
    }
    if(selectedItems().isEmpty())
    {
	qDebug("2222");
    }
    if(activePanel() == 0)
    {
	qDebug("3333");
    }
    if(itemAt(event->scenePos(), QTransform()) != 0)
    {
	qDebug("4444");
	MyItem *item;
	item = dynamic_cast<MyItem *>(itemAt(event->scenePos() , QTransform()));
	//	item = dynamic_cast<MyItem *>(itemAt(QPoint(350,240) , QTransform()));
	if(item != 0)
	qDebug() <<"text = " << item->text();
	    }*/
    MyMimeData *mimeData;
    QMimeData* data;
    data  = const_cast<QMimeData *>(event->mimeData());
    mimeData = dynamic_cast<MyMimeData *>(data);
    if(mimeData == 0)
	return ;
    MyItem *item = mimeData->item();
    // /* item move pos
    qDebug() << item->text();
    // */
    QGraphicsScene::dragMoveEvent(event);
}

void MyScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    qDebug("myScene dragdropEvent");
    QGraphicsScene::dropEvent(event);
}


/*void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "(" <<event->scenePos().x() <<","<<
	event->scenePos().y() <<")";
    QGraphicsScene::mouseMoveEvent(event);
    }*/

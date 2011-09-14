#ifndef _MYSCENE_H_
#define _MYSCENE_H_

#include <QGraphicsScene>

class MyScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MyScene();

    //    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
};
#endif

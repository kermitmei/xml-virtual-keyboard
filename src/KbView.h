#ifndef _KBVIEW_H_
#define _KBVIEW_H_


#include <QGraphicsView>
#include <QGraphicsScene>
#include <QtGui>

class KbView : public QGraphicsView
{
public:
    KbView(QWidget *parent = 0);


    QList<QGraphicsScene *> & sceneList()
    {
	return m_sceneList;
    }
private:
    QList<QGraphicsScene *> m_sceneList;
};
#endif//_KBVIEW_H_

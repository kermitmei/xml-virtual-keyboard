#ifndef _KBVIEW_H_
#define _KBVIEW_H_


#include <QGraphicsView>
#include <QGraphicsScene>
#include <QtGui>

class KbView : public QGraphicsView
{
public:
    KbView(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *event);
    
    void setSceneNum(int i)
    {
	if(m_sceneList.count() > 1)
	    this->setScene(m_sceneList[i]);
    }
    QList<QGraphicsScene *> & sceneList()
    {
	return m_sceneList;
    }
private:
    QList<QGraphicsScene *> m_sceneList;
    int m_count;
};
#endif//_KBVIEW_H_

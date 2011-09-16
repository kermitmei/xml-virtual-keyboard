#ifndef _KBVIEW_H_
#define _KBVIEW_H_


#include <QGraphicsView>
#include <QGraphicsScene>
#include <QtGui>
#include <QTimer>

class KbView : public QGraphicsView
{
    Q_OBJECT
public:
    KbView(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void setSceneNum(int i)
    {
	if(m_sceneList.count() > 1 && i < m_sceneList.count() )
	{
	    this->setScene(m_sceneList[i]);
	}
    }
    QList<QGraphicsScene *> & sceneList()
    {
	return m_sceneList;
    }
public slots:
    void moveView();
private:
    QList<QGraphicsScene *> m_sceneList;
    int m_count;
    bool m_moveView;
    QTimer  *m_timer;
    QPoint m_oldGlobalPos;
};
#endif//_KBVIEW_H_

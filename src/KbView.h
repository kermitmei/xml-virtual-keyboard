#ifndef _KBVIEW_H_
#define _KBVIEW_H_


#include <QGraphicsView>
#include "KbPage.h"
#include "KbItem.h"
#include <QtGui>
#include <QTimer>

class KbView : public QGraphicsView
{
    Q_OBJECT
public:
    KbView(QWidget *parent = 0);
    ~KbView();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void setSceneNum(int i)
    {
	if(m_pageList.count() > 1 && i < m_pageList.count() )
	{
	    this->setScene(m_pageList[i]);
	}
    }
    QList<KbPage *>& pageList()
    {
	return m_pageList;
    }
public slots:
    void moveView();
private:
    QList<KbPage *> m_pageList;
    int m_count;
    bool m_moveView;
    QTimer  *m_timer;
    QPoint m_oldGlobalPos;
};
#endif//_KBVIEW_H_

#ifndef _MYMIMEDATA_H_
#define _MYMIMEDATA_H_

#include <QMimeData>
#include "MyItem.h"
class MyItem;

class MyMimeData : public QMimeData
{
public:
    MyMimeData()
    {}
    void setItem(MyItem *item)
    {
	m_item = item;
    }
    MyItem* item() const
    {
	return m_item;
    }
    void setStartPos(QPointF pos)
    {
	m_pos = pos;
    }
    QPointF startPos()
    {
	return m_pos;
    }
private:
    MyItem *m_item;
    QPointF m_pos;
};
#endif

#ifndef _KBATTRIBUTE_H_
#define _KBATTRIBUTE_H_

#include <QtGui>
#include "PageAttribute.h"
class KbAttribute
{
public:
    KbAttribute():m_id(0),m_x(0),m_y(0),m_width(0),m_height(0)
    {}

    //set Foundation
    void setId(int id = 0)
    {
	m_id = id;
    }
    void setX(int x = 0)
    {
	m_x = x;
    }
    void setY(int y = 0)
    {
	m_y = y;
    }
    void setWidth(int width = 0)
    {
	m_width = width;
    }
    void setHeight(int height = 0)
    {
	m_height = height;
    }

    //get Foundation
    int id() const
    {
	return m_id;
    }
    int x() const
    {
	return m_x;
    }
    int y() const
    {
	return m_y;
    }
    int width() const
    {
	return m_width;
    }
    int height() const
    {
	return m_height;
    }
    QList<PageAttribute *> & pageList()
    {
	return m_pageList;
    }
    QList<QGraphicsScene *> & sceneList()
    {
	return m_sceneList;
    }
private:
    int m_id;
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    QList<PageAttribute *>  m_pageList;
    QList<QGraphicsScene *> m_sceneList;
};
#endif//_KBATTRIBUTE_H_

#ifndef _KBKEY_H_
#define _KBKEY_H_

#include <QGraphicsItem>
#include <QtGui>

#include "KbView.h"

class KbKey : public QGraphicsItem
{
public:
    KbKey();
    ~KbKey();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
public:
    // set and gei Foundation
    void setWidth(int width = 0)
    {
	m_width = width;
    }
    void setHeight(int height = 0)
    {
	m_height = height;
    }
    void setKeycode(int keycode = 0)
    {
	m_keycode = keycode;
    }
    void setText(QString text = NULL)
    {
	m_text = text;
    }
    void setBackground(QString background = NULL)
    {
	m_background = background;
	m_pixmap = new QPixmap(m_background);
	if(m_pixmap->isNull())
	{
	    qDebug("m_pixmap is null");
	    delete m_pixmap;
	    m_pixmap = 0;
	}
    }
    int width() const
    {
	return m_width;
    }
    int height()const
    {
	return m_height;
    }
    int keycode()const
    {
	return m_keycode;
    }
    QString text() const
    {
	return m_text;
    }
    QString background() const
    {
	return m_background;
    }
private:
    int     m_width;
    int     m_height;
    int     m_keycode;
    QString m_text;
    QString m_background;
    QPixmap *m_pixmap;
    bool    m_press;
};
#endif//_KBKEY_H_

#ifndef _KBCHECKABLE_H_
#define _KBCHECKABLE_H_

#include <QGraphicsItem>
#include <QtGui>

#include "KbView.h"

class KbCheckable : public QGraphicsItem
{
public:
    KbCheckable();
    virtual ~KbCheckable();

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
    void setCheckable(int checkable = 0)
    {
	m_checkable = checkable;
    }
    void setKeycode(int keycode = 0)
    {
	m_keycode = keycode;
    }
    void setText(QString text = NULL)
    {
	m_text = text;
    }
    void setBackground(QString background = NULL);
    int width() const
    {
	return m_width;
    }
    int height()const
    {
	return m_height;
    }
    int checkable() const
    {
	return m_checkable;
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
    int     m_checkable;
    int     m_keycode;
    QString m_text;
    QString m_background;
    QPixmap *m_pixmap;
    QPixmap *m_pixmapPressed;
    bool    m_press;
};
#endif//_KBCHECKABLE_H_

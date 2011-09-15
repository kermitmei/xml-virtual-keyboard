#ifndef _KBITEM_H_
#define _KBITEM_H_

#include <QGraphicsItem>
#include <QtGui>

class KbItem : public QGraphicsItem
{
public:
    KbItem();
    ~KbItem();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
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
};
#endif//_KBITEM_H_
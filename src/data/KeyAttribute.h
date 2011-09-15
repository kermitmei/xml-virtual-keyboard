#ifndef _KEYATTRIBUTE_H_
#define _KEYATTRIBUTE_H_

#include <QtGui>

class KeyAttribute
{
public:
    KeyAttribute():m_x(0),m_y(0),m_width(0),m_height(0),m_keycode(0)
    {}

    //set Foundation
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
    void setText(QString text = NULL)
    {
	m_text = text;
    }
    void setKeycode(int keycode = 0)
    {
	m_keycode = keycode;
    }
    void setBackground(QString background = NULL)
    {
	m_background = background;
    }
    //get Foundation
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
    QString text() const
    {
	return m_text;
    }
    int keycode() const
    {
	return m_keycode;
    }
    QString background() const
    {
	return m_background;
    }
private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    int m_keycode;
    QString m_text;
    QString m_background;
};
#endif//_KEYATTRIBUTE_H_

#ifndef _ITEMDATA_H_
#define _ITEMDATA_H_

#include <QString>

class ItemData
{
public:
    ItemData()
    {}
    void setX(int x = 0)
    {
	m_x = x;
    }
    void setY(int y = 0)
    {
	m_y = y;
    }
    void setWidth(int w = 0)
    {
	m_w = w;
    }
    void setHeigth(int h = 0)
    {
	m_h = h;
    }
    void setText(QString str = NULL)
    {
	m_str = str;
    }
    void setKeyCode(int keyCode)
    {
	m_keyCode = keyCode;
    }
    void setBackground(QString background = NULL)
    {
	m_background = background;
    }
    int x()
    {
	return m_x;
    }
    int y()
    {
	return m_y;
    }
    int width()
    {
	return m_w;
    }
    int heigth()
    {
	return m_h;
    }
    QString text()
    {
	return m_str;
    }
    int keyCode()
    {
	return m_keyCode;
    }
    QString background()
    {
	return m_background;
    }
private:
    int m_x;
    int m_y;
    int m_w;
    int m_h;
    QString m_str;
    int m_keyCode;
    QString m_background;
};
#endif

#ifndef _MYITEM_H_
#define _MYITEM_H_

#include <QtGui>
#include <QGraphicsItem>
#include "MyMimeData.h"

class MyItem : public QGraphicsItem
{
public:
    MyItem();
    
    QRectF boundingRect() const;
    
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

    void dragEnterEvent(QGraphicsSceneDragDropEvent* event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent* event);
    void dragMoveEvent (QGraphicsSceneDragDropEvent * event);

    void dropEvent(QGraphicsSceneDragDropEvent* event);


    //    bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const;
    QPainterPath  shape() const;
    void advance(int phase)
    {
	Q_UNUSED(phase);
    }

    void setText(QString text)
    {
	m_text = text;
    }
    void setWidth(int w)
    {
	m_width = w;
    }
    void setHeigth(int h)
    {
	m_heigth = h;
    }
    void setKeyCode(int keyCode)
    {
	m_keyCode = keyCode;
    }
    void setBackground(QString background)
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
    int width()const
    {
	return m_width;
    }
    int heigth() const
    {
	return m_heigth;
    }
    QString text() const
    {
	return m_text;
    }
    int keyCode() const
    {
	return m_keyCode;
    }
    QString background()const
    {
	return m_background;
    }
    bool press()
    {
	return m_press;
    }
private:
    void moveItem();
    void setColor(QColor color);
    void sendKey();
private:
    QColor  m_color;
    QPointF p;
    QString m_text;
    int     m_width;
    int     m_heigth;
    int     m_keyCode;
    QString m_background;
    bool    m_press;
    int     m_count;
    QPixmap *m_pixmap;
};
#endif

#ifndef _KBCHECKABLE_H_
#define _KBCHECKABLE_H_

#include <QGraphicsItem>
#include <QtGui>

#include "KbView.h"
#include "KbKey.h"

class KbCheckable : public KbKey
{
public:
    KbCheckable();
    virtual ~KbCheckable();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
public:
    // set and gei Foundation
    void setCheckable(int checkable = 0)
    {
	m_checkable = checkable;
    }
    void setBackground(QString background = NULL);
    int checkable() const
    {
	return m_checkable;
    }
private:
    int     m_checkable;
    QString m_background;
    QPixmap *m_pixmap;
    QPixmap *m_pixmapPressed;
    bool    m_press;
};
#endif//_KBCHECKABLE_H_

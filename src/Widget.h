#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <QtGui>
#include "MyItem.h"
#include "MyStreamReader.h"
#include "ItemData.h"
#include "MyScene.h"

class Widget : public QGraphicsView
{
    Q_OBJECT
public:
    Widget(QWidget* parent = 0);
    ~Widget();
protected:
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
public slots:
    void saveItemInfomation();
private:
    MyItem* m_item;
    MyStreamReader* m_xml;
    QList<ItemData*> m_list;
    MyScene *m_scene;
    QPushButton *m_saveBtn;
    QLineEdit   *m_lineEdit;
    QPoint       m_oldGlobalPos;
};
#endif

#ifndef _DROPVIEW_H_
#define _DROPVIEW_H_

#include <QtGui>

class DropView : public QGraphicsView
{
    Q_OBJECT
public:
    DropView(QWidget *parent = 0);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

    void mouseMoveEvent(QMouseEvent *event);
private:
    QTextEdit *textEdit;
};
#endif

#ifndef _KBPAGE_H_
#define _KBPAGE_H_

#include <QGraphicsScene>
class KbPage : public QGraphicsScene
{
public:
    KbPage(QObject *parent = 0);
    virtual ~KbPage();
};
#endif//_KBPAGE_H_

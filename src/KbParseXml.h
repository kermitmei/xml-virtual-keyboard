#ifndef _KBPARSEXML_H_
#define _KBPARSEXML_H_

#include <QtXml>
#include <QtGui>
#include <QList>

#include "./data/KbAttribute.h"
#include "./data/PageAttribute.h"
#include "./data/KeyAttribute.h"
#include "KbItem.h"
#include "KbView.h"

class KbParseXml
{
public:
    KbParseXml();;
    bool readFile(QString fileName);

    //write ItemData in xml
    bool writeXml(const QList<QGraphicsItem*> &list, QString fileName="save.xml");
    void writeIndexKey(QXmlStreamWriter *xmlWrite, const QList<QGraphicsItem*> &list);
    void initView();
private:
    void readViewElement();
    void readKeyboardElement();
    void readPageElement();
    void readKeyElement();
    void skipUnknownElement();

    QXmlStreamReader        reader;
    QList<KbAttribute *>    m_kbList;
    //    QList<PageAttribute *>  m_pageList;
    //    QList<KeyAttribute *>   m_keyList;
    //    QList<QGraphicsScene *> m_sceneList;
    KbView                 *m_view;
    QGraphicsScene          *m_scene;
    KbAttribute             *m_kb;
    PageAttribute           *m_page;
    KeyAttribute            *m_key;
};
#endif//_KBPARSEXML_H_

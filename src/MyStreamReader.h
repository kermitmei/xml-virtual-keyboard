#ifndef _MYSTREAMREADER_H_
#define _MYSTREAMREADER_H_

#include <QtXml>
#include <QtGui>
#include <QList>

#include "ItemData.h"
#include "MyItem.h"

class MyStreamReader
{
public:
    MyStreamReader();;
    bool readFile(QString fileName);
    QList<ItemData*> & getList()
    {
    	return m_list;
    }

    //write ItemData in xml
    bool writeXml(const QList<QGraphicsItem*> &list, QString fileName="save.xml");
    void writeIndexKey(QXmlStreamWriter *xmlWrite, const QList<QGraphicsItem*> &list);
private:
    void readKeyboardElement();
    void readKeyElement();
    void readPageElement();
    void skipUnknownElement();

    QXmlStreamReader reader;
    ItemData *m_itemData;
    QList<ItemData*>  m_list;
};
#endif

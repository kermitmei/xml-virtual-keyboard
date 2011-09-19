#ifndef _KBPARSEXML_H_
#define _KBPARSEXML_H_

#include <QtXml>
#include <QtGui>

#include "KbItem.h"
#include "KbView.h"
#include "KbPage.h"

class KbParseXml
{
public:
    KbParseXml();;
    bool readFile(QString fileName);
private:
    void readViewElement();
    void readKeyboardElement();
    void readPageElement();
    void readKeyElement();
    void skipUnknownElement();

    QXmlStreamReader        reader;
    KbView                  *m_view;
    KbPage                  *m_page;
    KbItem                  *m_item;
};
#endif//_KBPARSEXML_H_

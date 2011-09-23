#ifndef _KBPARSEXML_H_
#define _KBPARSEXML_H_

#include <QtXml>
#include <QtGui>

#include "KbKey.h"
#include "KbView.h"
#include "KbPage.h"
#include "KbCheckable.h"

class KbKey;
class KbCheckable;
class KbView;
class KbPage;
class KbParseXml
{
public:
    KbParseXml();;
    bool readFile(const QString &fileName);
private:
    void readViewElement();
    void readKeyboardElement();
    void readPageElement();
    void readKeyElement();
    void skipUnknownElement();

    QXmlStreamReader        m_reader;
    KbView                  *m_view;
    KbPage                  *m_page;
    KbKey                   *m_key;
    KbCheckable             *m_checkable;
};
#endif//_KBPARSEXML_H_

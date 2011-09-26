#ifndef _KBMANAGER_H_
#define _KBMANAGER_H_

#include "KbParseXml.h"
#include "PixmapBuf.h"
#include "KbKey.h"

extern "C"{
#include "UinputInterfact.h"
}

#define g_KbManager KbManager::instance()
class KbManager 
{
public:
    KbManager();
    virtual ~KbManager();

    bool loadXmlFile(const QString &fileName);
    
    static KbManager *instance();
    QList<KbView *>& kbViewList()
    {
	return m_kbViewList;
    }
    const QPixmap* getPixmap(const QString &localUrl)
    {
	return m_pixmapBuf.getPixmap(localUrl);
    }
protected:
    QList<KbView *>  m_kbViewList;
    PixmapBuf        m_pixmapBuf;
    KbParseXml       m_kbParseXml;
    static KbManager *m_kbManager;
};



#endif//_KBMANAGER_H_

#ifndef _KBMANAGER_H_
#define _KBMANAGER_H_

#define g_KbManager KbManager::instance()

class KbManager 
{
public:
    KbManager();
    ~KbManager();

    bool loadXmlFile(const QString &fileName);

    KbManager *instance();

protected:
    QList<KbView *>  m_kbViewList;
    PixmapBuf        m_pixmapBuf;
};



#endif//_KBMANAGER_H_

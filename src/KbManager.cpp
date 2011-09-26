#include "KbManager.h"

KbManager *KbManager::m_kbManager(0);

KbManager::KbManager()
{
#ifdef _X86_UINPUT_
    if(setup_uinput_device() < 0)
    {
	qDebug("Unable to find uinput device | usr root ");
	_exit(22);
    }
#endif //_X86_UINPUT_
    m_kbManager = this;
}

KbManager::~KbManager()
{
#ifdef _X86_UINPUT_
    ioctl(uinp_fd, UI_DEV_DESTROY);
    ::close(uinp_fd);
#endif //_X86_UINPUT_
    foreach(KbView *view, m_kbViewList)
    {
	if(view != 0)
	{
	    qDebug("delete view");
	    delete view;
	}
    }
}

KbManager *KbManager::instance()
{
    return m_kbManager;
}

bool KbManager::loadXmlFile(const QString &fileName)
{
    if(!m_kbParseXml.readFile(fileName))
	return false;
    return true;
}

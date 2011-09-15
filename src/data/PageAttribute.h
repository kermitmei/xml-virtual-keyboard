#ifndef _PAGEATTRIBUTE_H_
#define _PAGEATTRIBUTE_H_

#include <QtGui>
#include "KeyAttribute.h"

class PageAttribute
{
public:
    PageAttribute():m_pagekey(0)
    {}

    //set Foundation
    void setPagekey(int pagekey = 0)
    {
	m_pagekey = pagekey;
    }
    //get Foundation
    int pagekey() const
    {
	return m_pagekey;
    }
    QList<KeyAttribute *> & keyList()
    {
	return m_keyList;
    }
private:
    int m_pagekey;
    QList<KeyAttribute *> m_keyList;
};
#endif//_PAGEATTRIBUTE_H_

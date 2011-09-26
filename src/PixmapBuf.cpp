#include "PixmapBuf.h"

#include <QFileInfo>
#include <QPixmap>

PixmapInfo::PixmapInfo(const QString   &localUrl, 
		       const QDateTime &dateTime,
		       QPixmap   *pixmap )
    :m_localUrl(localUrl),
     m_dateTime(dateTime),
     m_pixmap(pixmap),
     m_sizeOfBytes(0)
{
    if(!m_pixmap->isNull()) {
	m_sizeOfBytes = m_pixmap->width() 
	    * m_pixmap->height() 
	    * m_pixmap->depth() / 8;
    }
}

PixmapInfo::~PixmapInfo()
{
    if(m_pixmap)
	delete m_pixmap;
}

PixmapBuf::~PixmapBuf()
{
    Node *tmp = m_head;
    while(m_head != m_last) {
	m_head = m_head->m_next;
	delete tmp;
	tmp = m_head;
    }
}

const PixmapInfo *PixmapBuf::getPixmapInfo(const QString &localUrl,
					   const QPixmap *pixmap)
{
    Node *rest = findNode(localUrl, pixmap);

    if(rest) {
	moveToFirst(rest);
	return rest->m_pixmapInfo;
    }

    //The rest doesn't exist.
    QFileInfo fileInfo(localUrl);
    if(!fileInfo.exists()) {
	qDebug("File (%s) Not be found!", qPrintable(localUrl));
	return 0;
    }

    //Create pixmap first
    QPixmap *newPixmap = new QPixmap(localUrl);
    if(newPixmap->isNull()) {
	delete newPixmap;
	return 0;
    }

    //create the PixmapInfo and then Node object.
    PixmapInfo *pixmapInfo = 
	new PixmapInfo(localUrl,fileInfo.lastModified(),newPixmap);
    rest = new Node(pixmapInfo);

    //New node should be move to the first.
    push_front(rest);
    return rest->m_pixmapInfo;
}

const QPixmap *PixmapBuf::getPixmap(const QString &localUrl, const QPixmap *pixmap)
{
    Node *rest = findNode(localUrl, pixmap);

    if(rest) {
	moveToFirst(rest);
	return rest->m_pixmapInfo->pixmap();
    }

    //The rest doesn't exist.
    QFileInfo fileInfo(localUrl);
    if(!fileInfo.exists()) {
	qDebug("File (%s) Not be found!", qPrintable(localUrl));
	return 0;
    }

    //Create pixmap first
    QPixmap *newPixmap = new QPixmap(localUrl);
    if(newPixmap->isNull()) {
	delete newPixmap;
	return 0;
    }

    //create the PixmapInfo and then Node object.
    PixmapInfo *pixmapInfo = 
	new PixmapInfo(localUrl,fileInfo.lastModified(),newPixmap);
    rest = new Node(pixmapInfo);

    //New node should be move to the first.
    push_front(rest);
    return rest->m_pixmapInfo->pixmap();
}

PixmapBuf::Node *PixmapBuf::findNode(const QString &localUrl, const QPixmap *pixmap)
{
    Node *currNode = m_head;
    while(currNode != 0) {
	if(pixmap) {
	    if(currNode->m_pixmapInfo->m_pixmap == pixmap) {
	        if(currNode->localUrl() == localUrl) 
		    return currNode;
	    }else {
		return 0;
	    }
	}else {
	    if(currNode->localUrl() == localUrl) {
		return currNode;
	    }
	}
	currNode = currNode->m_next;
    }
    return 0;
}

void PixmapBuf::moveToFirst(Node *node)
{
    if(m_head == m_last || m_head == node)
	return ;

    node->m_prior->m_next = node->m_next;

    if(node->m_next)
	node->m_next->m_prior = node->m_prior;
    else
	m_last = node->m_prior;

    node->m_prior = 0;
    node->m_next = m_head;

    //If Empty List.
    if(m_last == m_head)
	m_last = node;

    if(m_head)
	m_head->m_prior = node;
    m_head = node;
}

void PixmapBuf::deleteNode(Node *node)
{
    if(node->m_prior)
	node->m_prior->m_next = node->m_next;

    if(node->m_next)
	node->m_next->m_prior = node->m_prior;

    m_sizeOfBytes -= node->m_pixmapInfo->m_sizeOfBytes;
    --m_size;
    delete node;
}

void PixmapBuf::push_front(Node *node)
{
    node->m_prior = 0;
    node->m_next = m_head;

    //If Empty List.
    if(m_last == m_head)
	m_last = node;

    if(m_head)
	m_head->m_prior = node;
    m_head = node;
    ++m_size;
    m_sizeOfBytes += node->m_pixmapInfo->m_sizeOfBytes;
}

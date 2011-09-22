#ifndef _PIXMAPBUF_H_
#define _PIXMAPBUF_H_

#include <QDateTime>

class QPixmap;

class PixmapInfo
{
public:
    PixmapInfo(const QString   &localUrl, 
	       const QDateTime &dateTime,
	       QPixmap   *pixmap);

    ~PixmapInfo();

    const QPixmap *pixmap() const
    { return m_pixmap; }

    unsigned int sizeOfBytes() const
    { return m_sizeOfBytes; }

    QString      m_localUrl;
    QDateTime    m_dateTime;
    QPixmap     *m_pixmap;
    //How many bytes of memeory the m_pixmap takes.
    unsigned int m_sizeOfBytes;

protected:
    //You should not create a default object.
    PixmapInfo() { /* Do Nothing Here! */ }
};

class PixmapBuf
{
public:
    class Node
    {
    public:
	Node(PixmapInfo *pixmapInfo)
	    :m_prior(0), m_next(0),
	     m_pixmapInfo(pixmapInfo)
	{
	    //Do Nothing Here!
	}
	~Node()	{ delete m_pixmapInfo; }
	const QString &localUrl() const 
	{
	    return m_pixmapInfo->m_localUrl;
	}

	Node *m_prior;
	Node *m_next;
	PixmapInfo *m_pixmapInfo;
    protected:
	Node() { /* Do Nothing Here! */ }
    };

    PixmapBuf()
	:m_head(0),
	 m_last(0),
	 m_sizeOfBytes(0)
    { /* Do Nothing Here! */ }
    ~PixmapBuf();

    const PixmapInfo *getPixmapInfo(const QString &localUrl);

    unsigned int sizeOfBytes() const
    { return m_sizeOfBytes; }

    unsigned int size() const
    { return m_size; }


protected:
    Node *findNode(const QString &localUrl);
    void  moveToFirst(Node *node);
    void push_front(Node *node);

    //Delete a Node, and the Node must be in the list.
    void deleteNode(Node *node);

    Node *m_head;
    Node *m_last;
    unsigned int m_size;
    unsigned int m_sizeOfBytes;
};

#endif//_PIXMAPBUF_H_

#include "KbParseXml.h"
#include <QVariant>

KbParseXml::KbParseXml()
{

}

bool KbParseXml::readFile(QString fileName)
{
    QFile file(fileName);

    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
	qDebug() << "file open error ";
	return false;
    }

    reader.setDevice(&file);
    reader.readNext();
    while(!reader.atEnd())
    {
	if(reader.isStartElement())
	{
	    if(reader.name() == "view")
	    {
		readViewElement();
	    }
	    else
	    {
		reader.raiseError(QObject::tr("Not a keyboard file"));
	    }
	}
	else
	{
	    reader.readNext();
	}
    }
    file.close();
    if(reader.hasError())
    {
	qDebug() << "reader has error ";
	return false;
    }
    else if(file.error() != QFile::NoError)
    {
	qDebug() << "Can not read file";
	return false;
    }
    return true;
}

void KbParseXml::readViewElement()
{
    reader.readNext();
    while(!reader.atEnd())
    {
	if(reader.isEndElement())
	{
	    reader.readNext();
	    break;
	}
	if(reader.isStartElement())
	{
	    if(reader.name() == "keyboard")
	    {
		readKeyboardElement();
	    }
	    else
	    {
		skipUnknownElement();
	    }
	    
	}
	else
	{
	    reader.readNext();
	}
    }
}

void KbParseXml::readKeyboardElement()
{
    m_kb = new KbAttribute;
    m_kb->setId(reader.attributes().value("id").toString().toInt());
    m_kb->setX(reader.attributes().value("x").toString().toInt());
    m_kb->setY(reader.attributes().value("y").toString().toInt());
    m_kb->setWidth(reader.attributes().value("width").toString().toInt());
    m_kb->setHeight(reader.attributes().value("height").toString().toInt());
    m_kbList.append(m_kb);
    reader.readNext();
    while(!reader.atEnd())
    {
	if(reader.isEndElement())
	{
	    reader.readNext();
	    break;
	}
	if(reader.isStartElement())
	{
	    if(reader.name() == "page")
	    {
		readPageElement();
	    }
	    else
	    {
		skipUnknownElement();
	    }
	}
	else
	{
	    reader.readNext();
	}
    }
}

void KbParseXml::readPageElement()
{
    m_page = new PageAttribute;
    m_page->setPagekey(reader.attributes().value("pagekey").toString().toInt());
    m_kb->pageList().append(m_page);
    reader.readNext();
    while(!reader.atEnd())
    {
	if(reader.isEndElement())
	{
	    reader.readNext();
	    break;
	}
	if(reader.isStartElement())
	{
	    if(reader.name() == "key")
	    {
		//读取key的属性
		readKeyElement();
	    }
	    else
	    {
		skipUnknownElement();
	    }
	}
	else
	{
	    reader.readNext();
	}
    }
}

void KbParseXml::readKeyElement()
{
    m_key = new KeyAttribute;
    m_key->setX(reader.attributes().value("x").toString().toInt());
    m_key->setY(reader.attributes().value("y").toString().toInt());
    m_key->setWidth(reader.attributes().value("width").toString().toInt());
    m_key->setHeight(reader.attributes().value("height").toString().toInt());
    m_key->setText(reader.attributes().value("text").toString());
    m_key->setKeycode(reader.attributes().value("keycode").toString().toInt());
    m_key->setBackground(reader.attributes().value("background").toString());
    m_page->keyList().append(m_key);
    reader.readNext();
    while(!reader.atEnd())
    {
	if(reader.isEndElement())
	{
	    reader.readNext();
	    break;
	}
	else
	{
	    reader.readNext();
	}
    }
}



void KbParseXml::skipUnknownElement()
{
    reader.readNext();
    while(!reader.atEnd())
    {
	if(reader.isEndElement())
	{
	    reader.readNext();
	    break;
	}
	if(reader.isStartElement())
	{
	    skipUnknownElement();
	}
	else
	{
	    reader.readNext();
	}
    }
}


bool KbParseXml::writeXml(const QList<QGraphicsItem*> &list, QString fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
	qDebug("file open error");
	return false;
    }

    QXmlStreamWriter xmlWrite(&file);
    xmlWrite.setAutoFormatting(true);
    xmlWrite.writeStartDocument();
    xmlWrite.writeStartElement("keyboard");
    writeIndexKey(&xmlWrite, list);
    xmlWrite.writeEndDocument();
    file.close();
    if(file.error())
    {
	qDebug() << "cannot write file";
	return false;
    }
    return true;
}

void KbParseXml::writeIndexKey(QXmlStreamWriter *xmlWrite, const QList<QGraphicsItem*> &list)
{
    Q_UNUSED(xmlWrite);
    Q_UNUSED(list);
    /*    foreach(QGraphicsItem* item , list)
    {
	myItem = dynamic_cast<MyItem *>(item);
	if(myItem != 0)
	{
	    xmlWrite->writeStartElement("key");
	    xmlWrite->writeAttribute("x", QVariant(myItem->x()).toString());
	    xmlWrite->writeAttribute("y", QVariant(myItem->y()).toString());
	    xmlWrite->writeAttribute("width", QVariant(myItem->width()).toString());
	    xmlWrite->writeAttribute("heigth", QVariant(myItem->heigth()).toString());
	    xmlWrite->writeAttribute("text", myItem->text());
	    xmlWrite->writeAttribute("keycode", QVariant(myItem->keyCode()).toString());
	    xmlWrite->writeAttribute("background", myItem->background());
	    xmlWrite->writeEndElement();
	}
	}*/
}

void KbParseXml::initView()
{
    qDebug("initView");
    if(!m_kbList.isEmpty())
    {
	foreach(KbAttribute *kb , m_kbList)
	{
	    m_view = new KbView;
	    m_view->setGeometry(kb->x(), kb->y(), kb->width(), kb->height());
	    qDebug("x=%d, y=%d,w=%d,h=%d",kb->x(), kb->y(), kb->width(), kb->height());
	    foreach(PageAttribute *page, kb->pageList())
	    {
		qDebug("id = %d", page->pagekey());
		m_scene = new QGraphicsScene;
		foreach(KeyAttribute *key, page->keyList())
		{
		    KbItem *item = new KbItem;
		    item->setPos(key->x(), key->y());
		    item->setWidth(key->width());
		    item->setHeight(key->height());
		    item->setText(key->text());
		    item->setKeycode(key->keycode());
		    item->setBackground(key->background());
		    m_scene->addItem(item);
		    if(page->pagekey() == key->keycode())
		    {
			//			connect(key, SIGNAL(page(int)), m_view , SLOT(changeScenme(int)));
		    }
		}
		m_view->sceneList().append(m_scene);
	    }
	    m_view->setScene(m_view->sceneList()[0]);
	    m_view->show();
	}
    }
}

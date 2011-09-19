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
    m_view = new KbView;
    m_view->setGeometry(reader.attributes().value("x").toString().toInt(),
			reader.attributes().value("y").toString().toInt(),
			reader.attributes().value("width").toString().toInt(),
			reader.attributes().value("height").toString().toInt());
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
    m_view->setScene(m_view->pageList()[0]);
    m_view->show();
}

void KbParseXml::readPageElement()
{
    m_page = new KbPage;
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
    m_view->pageList().append(m_page);
}

void KbParseXml::readKeyElement()
{
    m_item = new KbItem;
    m_item->setX(reader.attributes().value("x").toString().toInt());
    m_item->setY(reader.attributes().value("y").toString().toInt());
    m_item->setWidth(reader.attributes().value("width").toString().toInt());
    m_item->setHeight(reader.attributes().value("height").toString().toInt());
    m_item->setText(reader.attributes().value("text").toString());
    m_item->setKeycode(reader.attributes().value("keycode").toString().toInt());
    m_item->setBackground(reader.attributes().value("background").toString());
    m_page->addItem(m_item);
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

#include "KbParseXml.h"
#include "KbManager.h"
#include <QVariant>

KbParseXml::KbParseXml()
{

}

bool KbParseXml::readFile(const QString &fileName)
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
    g_KbManager->kbViewList().append(m_view);
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
    m_key = new KbKey;
    m_key->setX(reader.attributes().value("x").toString().toInt());
    m_key->setY(reader.attributes().value("y").toString().toInt());
    m_key->setWidth(reader.attributes().value("width").toString().toInt());
    m_key->setHeight(reader.attributes().value("height").toString().toInt());
    m_key->setText(reader.attributes().value("text").toString());
    m_key->setKeycode(reader.attributes().value("keycode").toString().toInt());
    m_key->setBackground(reader.attributes().value("background").toString());
    m_page->addItem(m_key);
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

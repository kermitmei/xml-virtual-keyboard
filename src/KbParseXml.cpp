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

    m_reader.setDevice(&file);
    m_reader.readNext();
    while(!m_reader.atEnd())
    {
	if(m_reader.isStartElement())
	{
	    if(m_reader.name() == "view")
	    {
		readViewElement();
	    }
	    else
	    {
		m_reader.raiseError(QObject::tr("Not a keyboard file"));
	    }
	}
	else
	{
	    m_reader.readNext();
	}
    }
    file.close();
    if(m_reader.hasError())
    {
	qDebug() << "m_reader has error ";
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
    m_reader.readNext();
    while(!m_reader.atEnd())
    {
	if(m_reader.isEndElement())
	{
	    m_reader.readNext();
	    break;
	}
	if(m_reader.isStartElement())
	{
	    if(m_reader.name() == "keyboard")
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
	    m_reader.readNext();
	}
    }
}

void KbParseXml::readKeyboardElement()
{
    m_view = new KbView;
    m_view->setGeometry(m_reader.attributes().value("x").toString().toInt(),
			m_reader.attributes().value("y").toString().toInt(),
			m_reader.attributes().value("width").toString().toInt(),
			m_reader.attributes().value("height").toString().toInt());
    m_reader.readNext();
    while(!m_reader.atEnd())
    {
	if(m_reader.isEndElement())
	{
	    m_reader.readNext();
	    break;
	}
	if(m_reader.isStartElement())
	{
	    if(m_reader.name() == "page")
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
	    m_reader.readNext();
	}
    }
    m_view->setScene(m_view->pageList()[0]);
    g_KbManager->kbViewList().append(m_view);
    m_view->show();
}

void KbParseXml::readPageElement()
{
    m_page = new KbPage;
    m_reader.readNext();
    while(!m_reader.atEnd())
    {
	if(m_reader.isEndElement())
	{
	    m_reader.readNext();
	    break;
	}
	if(m_reader.isStartElement())
	{
	    if(m_reader.name() == "key")
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
	    m_reader.readNext();
	}
    }
    m_view->pageList().append(m_page);
}

void KbParseXml::readKeyElement()
{
    if(m_reader.attributes().value("checkable").isNull())
    {
	m_key = new KbKey;
	m_key->setX(m_reader.attributes().value("x").toString().toInt());
	m_key->setY(m_reader.attributes().value("y").toString().toInt());
	m_key->setWidth(m_reader.attributes().value("width").toString().toInt());
	m_key->setHeight(m_reader.attributes().value("height").toString().toInt());
	m_key->setText(m_reader.attributes().value("text").toString());
	m_key->setKeycode(m_reader.attributes().value("keycode").toString().toInt());
	m_key->setBackground(m_reader.attributes().value("background").toString());
	m_page->addItem(m_key);
    }
    else
    {
	m_checkable = new KbCheckable;
	m_checkable->setX(m_reader.attributes().value("x").toString().toInt());
	m_checkable->setY(m_reader.attributes().value("y").toString().toInt());
	m_checkable->setWidth(m_reader.attributes().value("width").toString().toInt());
	m_checkable->setHeight(m_reader.attributes().value("height").toString().toInt());
	m_checkable->setText(m_reader.attributes().value("text").toString());
	m_checkable->setKeycode(m_reader.attributes().value("keycode").toString().toInt());
	m_checkable->setBackground(m_reader.attributes().value("background").toString());
	m_checkable->setCheckable(m_reader.attributes().value("checkable").toString().toInt());
	m_page->addItem(m_checkable);
    }
    m_reader.readNext();
    while(!m_reader.atEnd())
    {
	if(m_reader.isEndElement())
	{
	    m_reader.readNext();
	    break;
	}
	else
	{
	    m_reader.readNext();
	}
    }
}



void KbParseXml::skipUnknownElement()
{
    m_reader.readNext();
    while(!m_reader.atEnd())
    {
	if(m_reader.isEndElement())
	{
	    m_reader.readNext();
	    break;
	}
	if(m_reader.isStartElement())
	{
	    skipUnknownElement();
	}
	else
	{
	    m_reader.readNext();
	}
    }
}

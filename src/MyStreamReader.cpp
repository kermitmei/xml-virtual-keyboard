#include "MyStreamReader.h"
#include <QVariant>

MyStreamReader::MyStreamReader()
{

}

bool MyStreamReader::readFile(QString fileName)
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
	    if(reader.name() == "keyboard")
	    {
		qDebug("keyboard");
		readKeyboardElement();
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

void MyStreamReader::readKeyboardElement()
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
	    if(reader.name() == "key")
	    {
		/*		qDebug("key");
		qDebug() << reader.attributes().value("x").toString();
		qDebug() << reader.attributes().value("y").toString();
		qDebug() << reader.attributes().value("w").toString();
		qDebug() << reader.attributes().value("h").toString();
		qDebug() << reader.attributes().value("text").toString();
		qDebug() << reader.attributes().value("background").toString();*/
		m_itemData = new ItemData;
		m_itemData->setX(reader.attributes().value("x").toString().toInt());
		m_itemData->setY(reader.attributes().value("y").toString().toInt());
		m_itemData->setWidth(reader.attributes().value("width").toString().toInt());
		m_itemData->setHeigth(reader.attributes().value("heigth").toString().toInt());
		m_itemData->setText(reader.attributes().value("text").toString());
		m_itemData->setKeyCode(reader.attributes().value("keycode").toString().toInt());
		m_itemData->setBackground(reader.attributes().value("background").toString());
		m_list.append(m_itemData);
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

void MyStreamReader::readKeyElement()
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

void MyStreamReader::readPageElement()
{
    
}

void MyStreamReader::skipUnknownElement()
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


bool MyStreamReader::writeXml(const QList<QGraphicsItem*> &list, QString fileName)
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

void MyStreamReader::writeIndexKey(QXmlStreamWriter *xmlWrite, const QList<QGraphicsItem*> &list)
{
    MyItem *myItem = 0;
    foreach(QGraphicsItem* item , list)
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
    }
}

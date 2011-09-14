#include "MyItem.h"

extern "C"{
#include "UinputInterfact.h"
}

MyItem::MyItem()
    :QGraphicsItem(),m_color(Qt::white), m_press(true),
     m_count(0), m_pixmap(0)
{
    setAcceptedMouseButtons(Qt::LeftButton);
    setAcceptDrops(true);
    setCursor(Qt::OpenHandCursor);
}

void MyItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    /*    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawRect(0 +m_dark,0 + m_dark,m_width+m_dark,m_heigth+m_dark);*/
    painter->setPen(QPen(Qt::black, 1));
    /*    if(m_press )
	  painter->setBrush(QBrush(QColor(85,85,85)));
    else
    painter->setBrush(QBrush(QColor(125,125,125)));*/
    
    if(m_pixmap != 0)
    {
	painter->drawPixmap(0,0,m_width, m_heigth, *m_pixmap);
    }
    else
    {
	painter->setBrush(QBrush(QColor(85,85,85)));
    }
    painter->drawRect(0,0,m_width,m_heigth);
    painter->setFont(QFont("Times", 18, QFont::Bold));
    painter->setPen(QPen(m_color, 1));
    painter->drawText(0,0,m_width, m_heigth, Qt::AlignCenter, m_text);
}

QRectF MyItem::boundingRect() const
{
    //    qreal adjust = 0.5;
    return QRectF(0,0, m_width, m_heigth);
}


void MyItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(m_count == 0)
    {
	m_press = false;
	//	qDebug("input keycode ...... then clicked save button");
	m_count = 1;
    }
    else
    {
	m_press = true;
	m_count = 0;
    }
    qDebug("item x = %s ,y = %s", 
	   QVariant(this->x()).toString().toUtf8().constData(),
	   QVariant(this->y()).toString().toUtf8().constData());
    
    MyMimeData *data=new MyMimeData;
    data->setColorData(Qt::red);
    data->setText(text());
    data->setStartPos(event->scenePos());
    data->setItem(this);
    QDrag *drag=new QDrag(event->widget());
    drag->setMimeData(data);
    drag->setHotSpot(event->pos().toPoint());
    QPixmap pixmap(width(), heigth());
    pixmap.fill(m_color);
    QPainter painter(&pixmap);
    paint(&painter, 0,0);
    painter.end();
    drag->setPixmap(pixmap);
    hide();
    drag->start();
    show();
    
    setCursor(Qt::OpenHandCursor);
    update();
    sendKey();
}

void MyItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    //    qDebug("mouseRelease");
    Q_UNUSED(event);
    setCursor(Qt::OpenHandCursor);
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void MyItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    //    qDebug("MyIten::mouseMoveEvent");
    p = event->scenePos();
    
    setPos(p.x() - 15, p.y() - 15);
    QList<QGraphicsItem *> list = scene()->collidingItems(this);
    if (!list.isEmpty())
    {
	MyItem *myItem = 0;
	foreach(QGraphicsItem *item, list)
	{
	    myItem = dynamic_cast<MyItem *>(item);
	    if(myItem != 0)
		myItem->setColor(m_color);
	}
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void MyItem::dragEnterEvent(QGraphicsSceneDragDropEvent* event)
{
    qDebug("dragEnterEvent in %s",qPrintable(m_text));
    event->setAccepted(event->mimeData()->hasFormat("text/plain"));
    QGraphicsItem::dragEnterEvent(event);
}

void MyItem::dragLeaveEvent(QGraphicsSceneDragDropEvent* event)
{
    qDebug("dragLeaveEvent in %s",qPrintable(m_text));
    QGraphicsItem::dragLeaveEvent(event);
}

void MyItem::dragMoveEvent (QGraphicsSceneDragDropEvent * event)
{
    qDebug("dragMoveEvent in %s",qPrintable(m_text));
    QGraphicsItem::dragMoveEvent(event);
}

void MyItem::dropEvent(QGraphicsSceneDragDropEvent* event)
{
    qDebug("MyItem::dropEvent");
    QGraphicsItem::dropEvent(event);
}

QPainterPath  MyItem::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void MyItem::moveItem()
{
    //    qDebug("peng zhuang le ");
}

void MyItem::setColor(QColor color)
{
    m_color = color;
    update();
}

void MyItem::sendKey()
{
    //    qDebug("key = %d", m_keyCode - 8);
    send_a_key(m_keyCode - 8);
}

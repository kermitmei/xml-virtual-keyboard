#include "Widget.h"

extern "C"{
#include "UinputInterfact.h"
}

Widget::Widget(QWidget* parent):QGraphicsView(parent),m_oldGlobalPos(0,0)
{
    setAcceptDrops(true);
    setWindowFlags(Qt::ToolTip);
    //        setWindowFlags(Qt::FramelessWindowHint);
    setMouseTracking(true);
    setFocusPolicy(Qt::NoFocus);
    if(setup_uinput_device() < 0)
    {
	qDebug("use root | unable to find uinput device");
	_exit(22);
    }
    m_saveBtn = new QPushButton("save", this);
    m_saveBtn->setGeometry(600,300,150,50);
    m_saveBtn->setFocusPolicy(Qt::NoFocus);
    connect(m_saveBtn, SIGNAL(clicked()),
	    this, SLOT(saveItemInfomation()));

    m_lineEdit = new QLineEdit(this);
    m_lineEdit->setGeometry(200,300,350,50);
    m_lineEdit->setFocusPolicy(Qt::StrongFocus);
    m_lineEdit->setFont(QFont("Times", 20, QFont::Bold));
    m_saveBtn->hide();
    m_lineEdit->hide();
    setGeometry(0,0,900,400);
    m_scene = new MyScene;
    //    m_scene->setSceneRect(0,0,750,550);

    m_xml = new MyStreamReader;
    m_xml->readFile("save.xml");
    m_list = m_xml->getList();
    if(!m_list.isEmpty())
    {
	foreach(ItemData *data , m_list)
	{
	    m_item = new MyItem;
	    
	    m_item->setPos(data->x(), data->y());
	    m_item->setText(data->text());
	    m_item->setWidth(data->width());
	    m_item->setHeigth(data->heigth());
	    m_item->setKeyCode(data->keyCode());
	    m_item->setBackground(data->background());
	    m_scene->addItem(m_item);
	}
    }
    setScene(m_scene);
    //    setGeometry(m_scene->sceneRect().x(), m_scene->sceneRect().y(),
    //		m_scene->sceneRect().width() + 25, m_scene->sceneRect().height() + 25);
    setRenderHint(QPainter::Antialiasing);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setBackgroundBrush(QColor(Qt::black));
}

void Widget::mousePressEvent(QMouseEvent* event)
{
    if( event->buttons() == Qt::LeftButton)
    {
	m_oldGlobalPos = event->globalPos();
    }
    QGraphicsView::mousePressEvent(event);
}

void Widget::mouseMoveEvent(QMouseEvent* event)
{
    //    qDebug("mouse x = %d, y = %d", event->x(), event->y());
    if( event->buttons() == Qt::LeftButton)
    {
	if(m_oldGlobalPos == QPoint(0,0))
	{
	    m_oldGlobalPos = event->globalPos();
	    return ;
	}
	
	int off_x = event->globalX() - m_oldGlobalPos.x();
	int off_y = event->globalY() - m_oldGlobalPos.y();
	m_oldGlobalPos.setX(event->globalX());
	m_oldGlobalPos.setY(event->globalY());

	move(this->x() + off_x, this->y() + off_y);
    }
}


void Widget::saveItemInfomation()
{
    qDebug("saveItemInfomation()");
    MyItem *myItem = 0;
    foreach(QGraphicsItem *item, m_scene->items())
    {
	myItem = dynamic_cast<MyItem* >(item);
	if(myItem->press() == false)
	{
	    qDebug("myItem modify myItem's keycode");
	    myItem->setKeyCode(m_lineEdit->text().toInt());
	}
    }
    m_xml->writeXml(m_scene->items());
}

void Widget::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug("widget dragEnterEvent..");
    event->acceptProposedAction();
    QGraphicsView::dragEnterEvent(event);
}

void Widget::dragLeaveEvent(QDragLeaveEvent *event)
{
    QGraphicsView::dragLeaveEvent(event);
}

void Widget::dragMoveEvent(QDragMoveEvent *event)
{
    update();
    QGraphicsView::dragMoveEvent(event);
}

void Widget::dropEvent(QDropEvent *event)
{
    qDebug("widget dropEvent..");
    QGraphicsView::dropEvent(event);
}

Widget::~Widget()
{
    ioctl(uinp_fd, UI_DEV_DESTROY);

    ::close(uinp_fd);
}


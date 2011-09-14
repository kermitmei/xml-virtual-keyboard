#include <QApplication>
#include "Widget.h"
#include "DropView.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    //    MyStreamReader my;
    //    my.readFile("test.xml");
    Widget w;
    //    w.resize(800,600);
    w.show();

    //    DropView view;
    //    view.show();
    
    return app.exec();
}

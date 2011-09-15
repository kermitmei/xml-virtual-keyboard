#include <QApplication>
#include "KbReadXml.h"

int main(int argc, char** argv)
{
    QApplication app(argc,argv);

    KbReadXml my;
    my.readFile("./save.xml");
    my.initView();
    return app.exec();
}

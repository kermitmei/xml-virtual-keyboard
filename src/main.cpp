#include <QApplication>
#include "KbParseXml.h"

int main(int argc, char** argv)
{
    QApplication app(argc,argv);
    
    KbParseXml my;
    my.readFile("./save.xml");
    return app.exec();
}

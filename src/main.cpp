#include <QApplication>
#include "KbManager.h"

int main(int argc, char** argv)
{
    QApplication app(argc,argv);
    
    KbManager manager;
    manager.loadXmlFile("./save.xml");
    return app.exec();
}

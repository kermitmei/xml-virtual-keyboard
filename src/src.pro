######################################################################
# Automatically generated by qmake (2.01a) Thu Sep 22 10:09:02 2011
######################################################################

TEMPLATE = app
TARGET = xmlvkb
DEPENDPATH += . pics
INCLUDEPATH += .
CONFIG += release
QT += xml

# Input
HEADERS += KbKey.h KbPage.h KbParseXml.h KbView.h PixmapBuf.h UinputInterfact.h
SOURCES += KbKey.cpp \
           KbPage.cpp \
           KbParseXml.cpp \
           KbView.cpp \
           main.cpp \
           PixmapBuf.cpp \
           UinputInterfact.c
RESOURCES += pics/images.qrc
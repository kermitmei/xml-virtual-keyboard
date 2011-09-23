######################################################################
# Automatically generated by qmake (2.01a) Thu Sep 22 10:09:02 2011
######################################################################

DEFINES += _X86_UINPUT_

TEMPLATE = app
TARGET = xmlvkb
DEPENDPATH += . pics
INCLUDEPATH += .
CONFIG += release
QT += xml

# Input
HEADERS += KbKey.h           \
           KbPage.h          \
           KbParseXml.h      \
           KbView.h          \
           PixmapBuf.h       \
           UinputInterfact.h \
           KbManager.h       
           
SOURCES += KbKey.cpp         \
           KbPage.cpp        \
           KbParseXml.cpp    \
           KbView.cpp        \
           main.cpp          \
           PixmapBuf.cpp     \
           UinputInterfact.c \
           KbManager.cpp
RESOURCES += pics/images.qrc


OBJECTS_DIR = $$_PRO_FILE_PWD_/bin
RCC_DIR = $$_PRO_FILE_PWD_/bin
MOC_DIR = $$_PRO_FILE_PWD_/bin
UI_DIR  = $$_PRO_FILE_PWD_/bin
UI_HEADERS_DIR = $$_PRO_FILE_PWD_/bin
UI_SOURCES_DIR = $$_PRO_FILE_PWD_/bin

#-------------------------------------------------
#
# Project created by QtCreator 2015-12-11T17:54:14
#
#-------------------------------------------------

QT       += core gui opengl multimedia


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = openGL-snake
TEMPLATE = app


SOURCES += main.cpp \
    glwidget.cpp \
    Zmeyka.cpp \
    ZmeykaEL.cpp \
    globject.cpp

HEADERS  += glwidget.h \
    Zmeyka.h \
    ZmeykaEL.h \
    globject.h

FORMS    +=

DISTFILES +=

RESOURCES += \
    resource.qrc



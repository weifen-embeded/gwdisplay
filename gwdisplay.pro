#-------------------------------------------------
#
# Project created by QtCreator 2016-01-18T17:29:53
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gwdisplay
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    tcpclient.cpp

HEADERS  += widget.h \
    tcpclient.h

FORMS    += widget.ui

RESOURCES += \
    image.qrc

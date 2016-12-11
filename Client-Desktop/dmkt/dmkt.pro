#-------------------------------------------------
#
# Project created by QtCreator 2016-12-11T22:55:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dmkt
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h \
    danmu.h

FORMS    += widget.ui
QT       += network
QT       += sql

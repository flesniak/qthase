#-------------------------------------------------
#
# Project created by QtCreator 2014-10-21T16:24:33
#
#-------------------------------------------------

QT       += core gui webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qthase
TEMPLATE = app

QMAKE_CXXFLAGS += -Wall -Werror

SOURCES += main.cpp\
    qthase.cpp \
    inspector.cpp \
    webview.cpp

HEADERS  += qthase.h \
    webview.h \
    inspector.h \
    text.h

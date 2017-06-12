#-------------------------------------------------
#
# Project created by QtCreator 2016-10-30T12:36:28
#
#-------------------------------------------------

QT       += core gui
QT += network widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chess-game
TEMPLATE = app

SOURCES += main.cpp\
    net/dialog.cpp \
    net/server.cpp \
    net/thread.cpp \
    net/gamethread.cpp


HEADERS  += net/dialog.h \
    net/server.h \
    net/thread.h \
    net/gamethread.h

SUBDIRS += \
    net/ChessServer.pro

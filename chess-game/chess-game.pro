#-------------------------------------------------
#
# Project created by QtCreator 2016-10-30T12:36:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chess-game
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    state.cpp \
    cell.cpp \
    piece.cpp \
    coordinate.cpp \
    player.cpp

HEADERS  += mainwindow.h \
    state.h \
    cell.h \
    piece.h \
    coordinate.h \
    player.h \
    color.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource_pieces_images.qrc

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
    player.cpp \
    controller.cpp \
    king.cpp \
    queen.cpp \
    rook.cpp \
    bishop.cpp \
    knight.cpp \
    pawn.cpp \
    specialmoveshandler.cpp \
    cellbutton.cpp \
    gameoptionswindow.cpp

HEADERS  += mainwindow.h \
    state.h \
    cell.h \
    piece.h \
    coordinate.h \
    player.h \
    color.h \
    controller.h \
    king.h \
    queen.h \
    rook.h \
    bishop.h \
    knight.h \
    pawn.h \
    specialmoveshandler.h \
    cellbutton.h \
    gameoptionswindow.h \
    gametype.h

FORMS    += mainwindow.ui \
    gameoptionswindow.ui

RESOURCES += \
    resource_pieces_images.qrc

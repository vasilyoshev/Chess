#-------------------------------------------------
#
# Project created by QtCreator 2016-10-30T12:36:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chess-game
TEMPLATE = app

INCLUDEPATH += pieces \
    gui \
    ai \
    chess-logic \
    chess-utils \
    chess-state

SOURCES += main.cpp\
        mainwindow.cpp \
    chess-state/state.cpp \
    chess-state/cell.cpp \
    pieces/piece.cpp \
    chess-logic/controller.cpp \
    chess-utils/coordinate.cpp \
    chess-state/player.cpp \
    pieces/king.cpp \
    pieces/queen.cpp \
    pieces/rook.cpp \
    pieces/bishop.cpp \
    pieces/knight.cpp \
    pieces/pawn.cpp \
    chess-logic/specialmoveshandler.cpp \
    gui/cellbutton.cpp \
    gui/gameoptionswindow.cpp \
    gui/uihelperfunc.cpp \
    chess-logic/checkchecker.cpp \
    ai/ai.cpp \
    gui/choosepiecewindow.cpp


HEADERS  += mainwindow.h \
    chess-state/state.h \
    chess-state/cell.h \
    pieces/piece.h \
    chess-utils/coordinate.h \
    chess-state/player.h \
    chess-utils/color.h \
    chess-logic/controller.h \
    pieces/king.h \
    pieces/queen.h \
    pieces/rook.h \
    pieces/bishop.h \
    pieces/knight.h \
    pieces/pawn.h \
    chess-logic/specialmoveshandler.h \
    gui/cellbutton.h \
    gui/gameoptionswindow.h \
    chess-state/gametype.h \
    gui/uihelperfunc.h \
    chess-logic/checkchecker.h \
    ai/ai.h \
    gui/choosepiecewindow.h


FORMS    += mainwindow.ui \
    gui/gameoptionswindow.ui \
    gui/choosepiecewindow.ui

RESOURCES += \
    gui/resource_pieces_images.qrc

DISTFILES += \
    ai/placeholder.txt

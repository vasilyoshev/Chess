#include "state.h"

State::State()
{
    board.resize(BOARD_SIZE,vector<Cell>(BOARD_SIZE));

    currentPlayerIndex = 0;
    currentPlayer = &players[currentPlayerIndex];
}

void State::setPiece(Piece* piece, Coordinate coordinate)
{
    if(!coordinate.isInBoard())
        return; // maybe exception ?

    board[coordinate.getRow()][coordinate.getColumn()].setPiece(piece);
}

Piece* State::getPiece(Coordinate coordinate) const
{
    if(!coordinate.isInBoard())
        return nullptr; // maybe exception ?

    return board[coordinate.getRow()][coordinate.getColumn()].getPiece();
}

const vector< vector<Cell> >& State::getBoard() const
{
    return board;
}

const Player* State::getCurrentPlayer() const
{
    return currentPlayer;
}

void State::nextPlayer()
{
    currentPlayerIndex = (currentPlayerIndex+1) % 2;
    currentPlayer = &players[currentPlayerIndex];
}

void State::initPlayer1(string name, Color color)
{
    players[0].setName(name);
    players[0].setColor(color);
}

void State::initPlayer2(string name, Color color)
{
    players[1].setName(name);
    players[1].setColor(color);
}

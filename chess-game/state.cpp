#include "state.h"

State::State()
{
    board.resize(BOARD_SIZE,vector<Cell>(BOARD_SIZE));
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

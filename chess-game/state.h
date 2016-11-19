#ifndef STATE_H
#define STATE_H

#include "cell.h"
#include "player.h"

const int BOARD_SIZE = 8;

class State
{
private:
    vector< vector<Cell> > board;

    Player players[2];
    Player* currentPlayer;
public:
    State();
    void setPiece(Piece* piece, Coordinate coordinate);
    Piece* getPiece(Coordinate coordinate) const;

    const vector< vector<Cell> >& getBoard() const;
};

#endif // STATE_H

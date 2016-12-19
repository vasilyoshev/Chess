#ifndef STATE_H
#define STATE_H

#include "cell.h"
#include "player.h"

const int BOARD_SIZE = 8;

class State {
private:
    vector< vector<Cell> > board;
    int currentPlayerIndex;
    Player players[2];
    Player* currentPlayer;

public:
    State();

    void setPiece(Piece* piece, Coordinate coordinate);
    Piece* getPiece(Coordinate coordinate) const;

    const Player* getCurrentPlayer() const;
    void nextPlayer();

    void initPlayer1(string name, Color color);
    void initPlayer2(string name, Color color);

    const vector< vector<Cell> >& getBoard() const;
};

#endif // STATE_H

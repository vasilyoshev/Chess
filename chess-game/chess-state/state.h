#ifndef STATE_H
#define STATE_H

#include "cell.h"
#include "player.h"
#include "gametype.h"

const int BOARD_SIZE = 8;

class State {
private:
    vector< vector<Cell> > board;
    int currentPlayerIndex;
    Player players[2];
    Player* currentPlayer;
    TGameType gameType;

public:
    State();
    State(const State& state);

    void setPiece(Piece* piece, Coordinate coordinate);
    Piece* getPiece(Coordinate coordinate) const;

    Player* getCurrentPlayer() const;
    void nextPlayer();

    void initPlayer1(string name, Color color);
    void initPlayer2(string name, Color color);
    void initGameType(TGameType gameType);

    const vector< vector<Cell> >& getBoard() const;

    void setCheckStatusCurrentPlayer(bool inCheck);
    bool getCheckStatusCurrentPlayer();
};

#endif // STATE_H

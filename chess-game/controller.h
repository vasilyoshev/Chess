#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>

#include "state.h"
#include "coordinate.h"
#include "player.h"
#include "specialmoveshandler.h"
#include "gametype.h"

class Controller
{
private:
    State state;
    SpecialMovesHandler specialMovesHandler;

    void initPieces();
    void initPlayers();
    void setPawnPieces(int row, Color color);
    void setMajorPieces(int row, Color color);
public:
    Controller();
    void movePiece(Coordinate source, Coordinate target);
    vector<Coordinate> getValidMoves(Coordinate click);
    void initState();
    const State& getState();
    void setFirstPlayerColor(Color color);
    void setGameType(TGameType gameType);
};

#endif // CONTROLLER_H

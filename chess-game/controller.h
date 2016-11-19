#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>

#include "state.h"
#include "coordinate.h"
#include "player.h"
#include "specialmoveshandler.h"

class Controller
{
private:
    State state;
    SpecialMovesHandler specialMovesHandler;

    void initPieces();
    void setPawnPieces(int row, Color color);
    void setMajorPieces(int row, Color color);
public:
    Controller();
    void movePiece(Coordinate source, Coordinate target);
    vector<Coordinate> getValidMoves(Coordinate click);
    void initState();
    const State& getState();
};

#endif // CONTROLLER_H

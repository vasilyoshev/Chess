#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>

#include "state.h"
#include "piece.h"
#include "coordinate.h"
#include "player.h"

class Controller
{
private:
    State state;
public:
    Controller();
    void movePiece(Coordinate source, Coordinate target, Player currentPlayer);
    vector<Coordinate> getPossibleMoves(Coordinate click, Player currentPlayer);
};

#endif // CONTROLLER_H

#ifndef AI_H
#define AI_H

#include <vector>
#include <QString>
#include "controller.h"


#include "piece.h"
#include "rook.h"
#include "king.h"
#include "pawn.h"
#include "queen.h"
#include "bishop.h"
#include "knight.h"



class Ai{

    private:

    Controller controller;

    int row;
    int column;

    public:

    Ai();

   vector<Coordinate> getAllRandomValidTurns(State state, Color color);

};

#endif // AI_H



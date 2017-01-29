#ifndef SPECAILMOVESHANDLER_H
#define SPECAILMOVESHANDLER_H

#include "state.h"

class SpecialMovesHandler {
private:
    static std::vector<Coordinate> filterInvalidMoves(const State& state, std::vector< std::vector<Coordinate> >& abstractMoves, const Color& attackingColor);

    static void getSpecialMoves(King *king, const State &state, std::vector<Coordinate> &abstractMoves, Coordinate kingCoordinate);
    static void getSpecialMoves(Queen *queen, const State &state, std::vector<Coordinate> &abstractMoves);
    static void getSpecialMoves(Rook *rook, const State &state, std::vector<Coordinate> &abstractMoves);
    static void getSpecialMoves(Bishop *bishop, const State &state, std::vector<Coordinate> &abstractMoves);
    static void getSpecialMoves(Knight *knight, const State &state, std::vector<Coordinate> &abstractMoves);
    static void getSpecialMoves(Pawn *pawn, const State &state, std::vector<Coordinate> &abstractMoves, Coordinate pawnCoordinate);

public:
    SpecialMovesHandler();

    static std::vector<Coordinate> getValidMoves(const State &state, Coordinate click);
};

#endif // SPECAILMOVESHANDLER_H

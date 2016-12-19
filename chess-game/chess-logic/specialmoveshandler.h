#ifndef SPECAILMOVESHANDLER_H
#define SPECAILMOVESHANDLER_H

#include "state.h"

class SpecialMovesHandler {
private:
    void filterInvalidMoves(const State &state, std::vector<Coordinate> &abstractMoves);

    void getSpecialMoves(King *king, const State &state, std::vector<Coordinate> &abstractMoves);
    void getSpecialMoves(Queen *queen, const State &state, std::vector<Coordinate> &abstractMoves);
    void getSpecialMoves(Rook *rook, const State &state, std::vector<Coordinate> &abstractMoves);
    void getSpecialMoves(Bishop *bishop, const State &state, std::vector<Coordinate> &abstractMoves);
    void getSpecialMoves(Knight *knight, const State &state, std::vector<Coordinate> &abstractMoves);
    void getSpecialMoves(Pawn *pawn, const State &state, std::vector<Coordinate> &abstractMoves);

public:
    SpecialMovesHandler();

    std::vector<Coordinate> getValidMoves(const State &state, Coordinate click);
};

#endif // SPECAILMOVESHANDLER_H

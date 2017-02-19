#ifndef CHECKCHECKER_H
#define CHECKCHECKER_H

#include "state.h"
#include "coordinate.h"
#include "color.h"

/**
 * @brief The CheckChecker class provides functions for checking if the game is in check or chackmate.
 * It also can filter moves which make the current player under check.
 */
class CheckChecker {
private:
    static Coordinate locateCurrentPlayerKing(const State& state);

public:
    static bool checkForCheck(const State& state);
    static bool isCellUnderAttack(const State& state, const Coordinate& cell, const Color& attackingColor);
    static bool checkForCheckmate(State& state);
    static vector<Coordinate> filterCheckMoves(State& state, const vector<Coordinate>& possibleMoves, const Coordinate& pieceCoordinates);
};

#endif // CHECKCHECKER_H

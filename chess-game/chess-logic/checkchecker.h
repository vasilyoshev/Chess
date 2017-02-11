#ifndef CHECKCHECKER_H
#define CHECKCHECKER_H

#include "state.h"
#include "coordinate.h"
#include "color.h"

class CheckChecker {
private:
    static Coordinate locateCurrentPlayerKing(const State& state);
    static bool checkForCheckmate(const State& state, const Coordinate& king, const Color& attackingColor);
    static Color getOtherPlayerColor(const State& state);

public:
    static bool checkForCheck(const State& state);
    static bool checkForCheck(const State& state, const Coordinate& position, const Color& attackingColor);
    static bool checkForCheckmate(const State& state);
    static vector<Coordinate> filterCheckMoves(const State& state, vector<Coordinate> possibleMoves, const Coordinate& piece);
};

#endif // CHECKCHECKER_H

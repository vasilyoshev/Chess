#ifndef STATE_H
#define STATE_H

#include "cell.h"
#include "player.h"

class State
{
private:
    Cell board[8][8];
    Player players[2];
    Player* currentPlayer;
public:
    State();
};

#endif // STATE_H

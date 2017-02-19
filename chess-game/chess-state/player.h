#ifndef PLAYER_H
#define PLAYER_H

#include "color.h"
#include <string>

using namespace std;

/**
 * @brief The Player class stores the properties of a given player.
 */
class Player {
private:
    string name;
    Color color;
    bool inCheck;
    bool inCheckmate;

public:
    Player();
    Player(const Player& player);

    void setName(string name);
    string getName() const;

    void setColor(Color color);
    Color getColor() const;

    void setInCheck(bool inCheck);
    bool isInCheck() const;

    void setInCheckmate(bool inCheckmate);
    bool isInCheckmate() const;
};

#endif // PLAYER_H

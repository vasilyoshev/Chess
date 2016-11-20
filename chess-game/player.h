#ifndef PLAYER_H
#define PLAYER_H

#include "color.h"
#include <string>

using namespace std;

class Player
{
private:
    string name;
    Color color;
public:
    Player();

    void setName(string name);
    string getName() const;
    void setColor(Color color);
    Color getColor() const;

};

#endif // PLAYER_H

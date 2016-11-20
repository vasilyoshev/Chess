#include "player.h"

Player::Player()
{

}

string Player::getName() const
{
    return name;
}

Color Player::getColor() const
{
    return color;
}

void Player::setName(string name)
{
    this->name = name;
}

void Player::setColor(Color color)
{
    this->color = color;
}

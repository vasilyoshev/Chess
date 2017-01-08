#include "player.h"

Player::Player() {
    inCheck = false;
    inCheckmate = false;
}

Player::Player(const Player& player) {
    this->name = player.name;
    this->color = player.color;
    this->inCheck = player.inCheck;
}

string Player::getName() const {
    return name;
}

Color Player::getColor() const {
    return color;
}

bool Player::isInCheck() const {
    return inCheck;
}

bool Player::isInCheckmate() const {
    return inCheckmate;
}

void Player::setName(string name) {
    this->name = name;
}

void Player::setColor(Color color) {
    this->color = color;
}

void Player::setInCheck(bool inCheck) {
    this->inCheck = inCheck;
}

void Player::setInCheckmate(bool inCheckmate) {
    this->inCheckmate = inCheckmate;
}

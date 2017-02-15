#include "player.h"

/**
 * @brief Player::Player
 * Default constructor sets inCheck and inCheckmate flags to false.
 */
Player::Player() {
    inCheck = false;
    inCheckmate = false;
}

/**
 * @brief Player::Player
 * Copy constructor.
 *
 * @param player the player to copy
 */
Player::Player(const Player& player) {
    this->name = player.name;
    this->color = player.color;
    this->inCheck = player.inCheck;
    this->inCheckmate = player.inCheckmate;
}

/**
 * @brief Player::getName
 * Returns the name of the Player.
 *
 * @return the name of the Player
 */
string Player::getName() const {
    return name;
}

/**
 * @brief Player::getColor
 * Returns the color of the player.
 *
 * @return the color of the player
 */
Color Player::getColor() const {
    return color;
}

/**
 * @brief Player::isInCheck
 *
 * @return true if the player is in check
 */
bool Player::isInCheck() const {
    return inCheck;
}

/**
 * @brief Player::isInCheckmate
 *
 * @return true if the player is in checkmate
 */
bool Player::isInCheckmate() const {
    return inCheckmate;
}

/**
 * @brief Player::setName
 * Sets the name of the player.
 *
 * @param name the name to set
 */
void Player::setName(string name) {
    this->name = name;
}

/**
 * @brief Player::setColor
 * Sets the color of the player.
 *
 * @param color the color to set
 */
void Player::setColor(Color color) {
    this->color = color;
}

/**
 * @brief Player::setInCheck
 * Sets the inCheck flag
 *
 * @param inCheck the flag to set
 */
void Player::setInCheck(bool inCheck) {
    this->inCheck = inCheck;
}

/**
 * @brief Player::setInCheckmate
 * Sets the inCheckmate flag
 *
 * @param inCheckmate the flag to set
 */
void Player::setInCheckmate(bool inCheckmate) {
    this->inCheckmate = inCheckmate;
}

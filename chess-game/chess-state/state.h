#ifndef STATE_H
#define STATE_H

#include "cell.h"
#include "player.h"
#include "gametype.h"


const int BOARD_SIZE = 8;

/**
 * @brief The State class contains the state of the game
 */
class State {
private:
    vector< vector<Cell> > board;
    Player players[2];
    Player* currentPlayer;
    int currentPlayerIndex;
    TGameType gameType;
    bool inPawnPromotion;
    Coordinate pawnInPromotionCoordinates;

    void initPieces();
    void setPawnPieces(int row, Color color);
    void setMajorPieces(int row, Color color);

public:
    State();
    State(const State &state);

    void setPiece(Piece* piece, Coordinate coordinate);
    Piece* getPiece(Coordinate coordinate) const;

    Player* getCurrentPlayer() const;
    void nextPlayer();

    void setPlayer1(string name, Color color);
    void setPlayer2(string name, Color color);

    void setGameType(TGameType gameType);
    TGameType getGameType();

    bool getCheckStatusCurrentPlayer() const;

    bool isInPawnPromotion() const;
    void setInPawnPromotion(bool inPawnPromotion);

    void setPawnInPromotionCoordinates(Coordinate pawnInPromotionCoordinates);
    Coordinate getPawnInPromotionCoordinates() const;

};

#endif // STATE_H

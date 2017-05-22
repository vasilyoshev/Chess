#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include <QString>

#include "state.h"
#include "coordinate.h"
#include "player.h"
#include "specialmoveshandler.h"
#include "gametype.h"
#include "piece.h"

#include "rook.h"



/**
 * @brief The Controller class responsible for making all changes to the state.
 */
class Controller {
private:
    State state;

   // void initPieces();
   // void initPlayers();
    void setPawnPieces(int row, Color color);
    void setMajorPieces(int row, Color color);


    bool isLeftCastle(Piece::PieceType pieceType, Coordinate source, Coordinate target);
    bool isRightCastle(Piece::PieceType pieceType, Coordinate source, Coordinate target);
    void doCastle(Piece* sourcePiece, Coordinate source, Coordinate rookTarget, Coordinate target, Coordinate rookSource);
    void changePlayer();
    void checkAndSetPawnPromotion(Piece* sourcePiece, Coordinate& pieceCoordinate);

public:
    Controller();
    void movePiece(Coordinate source, Coordinate target);
    vector<Coordinate> getValidMoves(Coordinate click);
    Piece* getPiece(Coordinate coordinate);
    Player* getCurrentPlayer();
    void setFirstPlayer(string name, Color color);
    void setSecondPlayer(string name, Color color);
    void setGameType(TGameType gameType);
    void setWhitePlayerInTurn();
    void promotePawn(Piece::PieceType pieceType);
    bool isInPawnPromotion();


    std::vector<Coordinate> getAiTurn(State state);


};

#endif // CONTROLLER_H

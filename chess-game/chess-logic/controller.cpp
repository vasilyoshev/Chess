

#include "controller.h"
#include "piece.h"
#include "checkchecker.h"


/**
 * @brief Controller::Controller
 */
Controller::Controller() {
}

/**
 * @brief Controller::getValidMoves
 * Returns the valid moves for the piece which is clicked.
 * A valid move is a move permitted according to the piece type and does not place the current player under check.
 * If the click is outside the board or on empty cell, an empty vector is returned.
 *
 * @param click the coordinates of the click
 * @return vector containing the coordinates that the piece can be moved to
 */
vector<Coordinate> Controller::getValidMoves(Coordinate click) {
    if(!click.isInBoard()) {
        return vector<Coordinate>();
    }

    return CheckChecker::filterCheckMoves(state, SpecialMovesHandler::getValidMoves(state, click), click);
}

/**
 * @brief Controller::getPiece
 * Returns a reference to the piece located on the provided coordinate.
 * If there is no piece on the coordinate null pointer is returned.
 *
 * @param coordinate the coordinate for which the piece is requested
 * @return a reference to the piece located on that coordinate, null pointer if there is no piece at that coordinate
 */
Piece* Controller::getPiece(Coordinate coordinate) {
    return state.getPiece(coordinate);
}

/**
 * @brief Controller::getCurrentPlayer
 * Returns a reference to the player who is in turn.
 *
 * @return a reference to the player who is in turn
 */
Player* Controller::getCurrentPlayer() {
    return state.getCurrentPlayer();
}

/**
 * @brief Controller::isLeftCastle
 *
 * @param pieceType - type of the piece
 * @param source - coordinates of source position
 * @param target - coordinates of target position
 *
 * @return true if the selected move is for queenside castling
 */
bool Controller::isLeftCastle(Piece::PieceType pieceType, Coordinate source, Coordinate target) {
    return pieceType==Piece::PieceType::ptKing && target.getColumn()==source.getColumn()-2;
}

/**
 * @brief Controller::isLeftCastle
 *
 * @param pieceType - type of the piece
 * @param source - coordinates of source position
 * @param target - coordinates of target position
 *
 * @return true if the selected move is for kingside castling
 */
bool Controller::isRightCastle(Piece::PieceType pieceType, Coordinate source, Coordinate target) {
    return pieceType==Piece::PieceType::ptKing && target.getColumn()==source.getColumn()+2;
}

/**
 * @brief Controller::doCastle
 *
 * Performs the castling move.
 *
 * @param sourcePiece - king piece
 * @param source - coordinates of king source
 * @param rookTarget - coordinates of rook target
 * @param target - coordinates of king target
 * @param rookSource - coordinates of rook source
 */
void Controller::doCastle(Piece* sourcePiece, Coordinate source, Coordinate rookTarget, Coordinate target, Coordinate rookSource)
{
    Piece* rook = state.getPiece(rookSource);

    //move king to new position
    state.setPiece(sourcePiece, target);
    state.setPiece(nullptr, source);

    //move rook to new position
    state.setPiece(rook, rookTarget);
    state.setPiece(nullptr, rookSource);

    //set flags for king and rook
    sourcePiece->setMoved();
    rook->setMoved();

    changePlayer();
}

/**
 * @brief Controller::movePiece
 * Moving a piece from the source coordinates to the target ones
 *
 * @param source the current coordinates of the piece
 * @param target the coordinates where the piece should be moved
 */
void Controller::movePiece(Coordinate source, Coordinate target) {
    Piece* sourcePiece = state.getPiece(source);

    //if move is queenside castling
    if(isLeftCastle(sourcePiece->getType(), source, target)) {
        Coordinate rookSource = Coordinate(target.getRow(), target.getColumn() - 2);
        Coordinate rookTarget = Coordinate(target.getRow(), target.getColumn() + 1);
        doCastle(sourcePiece, source, rookTarget, target, rookSource);

    //if move is kingside castling
    } else if(isRightCastle(sourcePiece->getType(), source, target)) {
        Coordinate rookSource = Coordinate(target.getRow(), target.getColumn() + 1);
        Coordinate rookTarget = Coordinate(target.getRow(), target.getColumn() - 1);
        doCastle(sourcePiece, source, rookTarget, target, rookSource);

    //if move is not castling
    } else {
        Piece* targetPiece = state.getPiece(target);
        delete targetPiece; // deleting the piece on the target coordinates if it exists
        state.setPiece(sourcePiece, target); // making the move
        state.setPiece(nullptr, source);

        sourcePiece->setMoved();

        state.getCurrentPlayer()->setInCheck(false);

        // checking if after the move a pown is in promotion
        checkAndSetPawnPromotion(sourcePiece, target);
        if(!state.isInPawnPromotion()) {
            // change player if there is no pown in promotion
            changePlayer();
        }
    }
}

/**
 * @brief Controller::checkAndSetPawnPromotion
 * Checks if the provided piece is a pawn in promotion (in the first orr last row depending on the color).
 * If the provided piece is indeed a pawn in promotion the corrsponding flag is updated.
 *
 * @param sourcePiece the provided piece
 * @param pieceCoordinate the coordinates of the piece
 */
void Controller::checkAndSetPawnPromotion(Piece* sourcePiece, Coordinate& pieceCoordinate) {
    if (sourcePiece->getType() == Piece::PieceType::ptPawn &&
            ((sourcePiece->getColor() == cWhite && pieceCoordinate.getRow() == 0) ||
             (sourcePiece->getColor() == cBlack && pieceCoordinate.getRow() == 7))) {
        state.setInPawnPromotion(true);
        state.setPawnInPromotionCoordinates(pieceCoordinate); // caches the coordinates for later
    }
}

/**
 * @brief Controller::promotePawn
 * Changes the pawn which is in promotion to the provided type
 *
 * @param pieceType the type of piece that should be created in the place of the pawn which is in promotion
 */
void Controller::promotePawn(Piece::PieceType pieceType) {
    Coordinate pawnCoordinate = state.getPawnInPromotionCoordinates();

    Piece* pawn = state.getPiece(pawnCoordinate);
    Color pawnColor = pawn->getColor();
    delete pawn; // removin the pown

    // creating the new piece
    if (pieceType == Piece::PieceType::ptQueen) {
        state.setPiece(new Queen(pawnColor), pawnCoordinate);
    } else if (pieceType == Piece::PieceType::ptKnight) {
        state.setPiece(new Knight(pawnColor), pawnCoordinate);
    } else if (pieceType == Piece::PieceType::ptRook) {
        state.setPiece(new Rook(pawnColor), pawnCoordinate);
    } else if (pieceType == Piece::PieceType::ptBishop) {
        state.setPiece(new Bishop(pawnColor), pawnCoordinate);
    }

    state.setInPawnPromotion(false);
    state.setPawnInPromotionCoordinates(Coordinate(-1, -1));
    changePlayer();
}

/**
 * @brief Controller::isInPawnPromotion
 *
 * @return true if there is a pawn in promotion (in first or last row depending on the color)
 */
bool Controller::isInPawnPromotion(){
    return state.isInPawnPromotion();
}

/**
 * @brief Controller::changePlayer
 * Updates the player in turn.
 */
void Controller::changePlayer() {
    state.nextPlayer();

    // checking if the current player is in check
    if (CheckChecker::checkForCheck(state)) {
        state.getCurrentPlayer()->setInCheck(true);
        // checking for checkmate only if the player is in check
        state.getCurrentPlayer()->setInCheckmate(CheckChecker::checkForCheckmate(state));
    }
}

/**
 * @brief Controller::setFirstPlayer
 * Sets the first player.
 *
 * @param name the name of the player
 * @param color the color of the player
 */
void Controller::setFirstPlayer(string name, Color color) {
    state.setPlayer1(name,color);
}

/**
 * @brief Controller::setSecondPlayer
 * Sets the second player.
 *
 * @param name the name of the player
 * @param color the color of the player
 */
void Controller::setSecondPlayer(string name, Color color) {
    state.setPlayer2(name,color);
}

/**
 * @brief Controller::setGameType
 * Sets the game type
 *
 * @param gameType the game type
 */
void Controller::setGameType(TGameType gameType) {
    state.setGameType(gameType);
}

/**
 * @brief Controller::setWhitePlayerInTurn
 * Sets the white player to be in turn
 */
void Controller::setWhitePlayerInTurn() {
    if(state.getCurrentPlayer()->getColor() != cWhite) {
        state.nextPlayer();
    }
}

std::vector<Coordinate> Controller::getAiTurn(State state){

             vector<Coordinate> piecePositions;  // creates vector for the figure coordinates
             for (int row = 0; row < 8; row++){
                for (int column = 0; column < 8; column++){

                    Coordinate piecePosition = Coordinate(row, column);
                    Piece* piece2 = state.getPiece(piecePosition); //element.position.
                    //Gets the piece on the board on the corresponding column and row

                    Color pieceColor = piece2->getColor(); //gets the color of the piece2
                    Color aiPlayerColor = state.getCurrentPlayer()->getColor(); //gets the color of the current player


                    if ( pieceColor == aiPlayerColor ){ // checks if the color of piece2 is the same as the current player
                    piecePositions.push_back(Coordinate(row, column)); // pushes the coordinates in the vector
                    }
                }
            }


            return piecePositions;
    }

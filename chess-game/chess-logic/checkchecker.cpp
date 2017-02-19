#include <vector>

#include "state.h"
#include "piece.h"
#include "color.h"
#include "coordinate.h"
#include "checkchecker.h"
#include "specialmoveshandler.h"

/**
 * @brief CheckChecker::checkForCheck
 *
 * Checks if the current player in provided state is in check.
 *
 * @param state a game state
 * @return true if the current player is in check, false otherwise.
 */
bool CheckChecker::checkForCheck(const State& state) {
    Coordinate king = locateCurrentPlayerKing(state);
    Color otherPlayerColor = ColorUtils::getOppositeColor(state.getCurrentPlayer()->getColor());

    return isCellUnderAttack(state, king, otherPlayerColor);
}

/**
 * @brief CheckChecker::checkForCheckmate
 *
 * Checks if the current player in provided state is in checkmate.
 *
 * @param state a game state
 * @return true if the current player is in checkmate, false otherwise
 */
bool CheckChecker::checkForCheckmate(State& state) {
    if(!checkForCheck(state)) {
        return false;
    }

    Color currentPlayerColor = state.getCurrentPlayer()->getColor();

    //checking if the current player can make a valid move with his pieces
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int column = 0; column < BOARD_SIZE; column++) {
            Piece* piece = state.getPiece(Coordinate(row, column));

            if (piece != NULL && piece->getColor() == currentPlayerColor) {
                Coordinate coordinate = Coordinate(row, column);

                // if getValidMoves returns non empty list it means that the current player can make a valid move (without being in chess)
                if (!filterCheckMoves(state, SpecialMovesHandler::getValidMoves(state, coordinate), coordinate).empty() ) {
                    return false;
                }
            }
        }
    }

    // there were no possible moves -> the current player is in checkmate
    return true;
}

/**
 * @brief CheckChecker::isCellUnderAttack
 *
 * Checks if the provided cell is under attack.
 *
 * @param state the state of the game
 * @param cell the cell which has to be checked
 * @param attackingColor the color of the player who is attacking
 * @return true if the cell is under attack by the attackingColor, false otherwise.
 */
bool CheckChecker::isCellUnderAttack(const State& state, const Coordinate& cell, const Color& attackingColor) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int column = 0; column < BOARD_SIZE; column++) {
            Piece* piece = state.getPiece(Coordinate(row, column));

            if (piece != NULL && piece->getColor() == attackingColor) {
                // Stops cyclic castle check between the two kings.
                // If both kings had not been moved, do not check if one atacks the other.
                if(piece->getType()==Piece::ptKing && !piece->getMoved()) {
                    King* currentKing = (King*) state.getPiece(locateCurrentPlayerKing(state));
                    if(!currentKing->getMoved()) {
                        continue;
                    }
                }

                vector<Coordinate> attackingPositions = SpecialMovesHandler::getValidMoves(state, Coordinate(row, column));

                for (std::size_t i=0; i<attackingPositions.size(); i++) {
                    if (attackingPositions[i] == cell) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

/**
 * @brief CheckChecker::locateCurrentPlayerKing
 *
 * Locates the king of the current player.
 *
 * @param state a game state
 * @return the coordinates of the king of the current player
 */
Coordinate CheckChecker::locateCurrentPlayerKing(const State& state) {
    Color currentPlayerColor = state.getCurrentPlayer()->getColor();

    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int column = 0; column < BOARD_SIZE; column++) {
            Piece* piece = state.getPiece(Coordinate(row, column));

            if (piece != NULL && piece->getType() == Piece::ptKing && piece->getColor() == currentPlayerColor) {
                return Coordinate(row, column);
            }
        }
    }

    // no king found
    return Coordinate(-1, -1);
}

/**
 * @brief CheckChecker::filterCheckMoves
 *
 * Filters the moves which makes the current player under check.
 *
 * @param state a game state
 * @param possibleMoves vector containing the possible moves of the selected piece
 * @param pieceCoordinates the selected piece coordinates
 * @return the provided moves without the ones which put the current player under check
 */
vector<Coordinate> CheckChecker::filterCheckMoves(State& state,
                                                  const vector<Coordinate>& possibleMoves,
                                                  const Coordinate& pieceCoordinates) {
    vector<Coordinate> filtered;

    for (std::size_t i = 0; i < possibleMoves.size(); i++) {
        Coordinate target = possibleMoves[i];

        // copy the state
        State afterMove = State(state);

        // make the move
        Piece* sourcePiece = afterMove.getPiece(pieceCoordinates);
        Piece* targetPiece = afterMove.getPiece(target);
        delete targetPiece;
        afterMove.setPiece(nullptr, pieceCoordinates);
        afterMove.setPiece(sourcePiece, target);

        // adding the move if it does not put the current player in check
        if (!checkForCheck(afterMove)) {
            filtered.push_back(possibleMoves[i]);
        }
    }

    return filtered;
}

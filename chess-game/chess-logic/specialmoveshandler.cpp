#include "specialmoveshandler.h"
#include "checkchecker.h"

SpecialMovesHandler::SpecialMovesHandler() {
}

/**
 * @brief SpecialMovesHandler::getValidMoves
 *
 * Gets all moves for the selected piece in the current state.
 *
 * @param state - the game state
 * @param click - coordinates of the clicked field
 *
 * @return all valid moves for a selected piece
 */
std::vector<Coordinate> SpecialMovesHandler::getValidMoves(const State& state, Coordinate click) {
    Piece* p = state.getPiece(click);
    std::vector< vector<Coordinate> > result = p->getPossibleMoves(click);

    std::vector<Coordinate> moves;
    moves = filterInvalidMoves(state, result, p->getColor());

    switch(p->getType()) {
    case Piece::ptKing :
        getSpecialMoves((King*)p, state, moves, click);
        break;
    case Piece::ptPawn :
        getSpecialMoves((Pawn*)p, state, moves, click);
        break;
    default:
        // empty
        break;
    }

    return moves;
}

/**
 * @brief SpecialMovesHandler::filterInvalidMoves
 *
 * Filters possible moves blocked by other pieces.
 *
 * @param state - the game state
 * @param abstractMoves - possible moves of the piece
 * @param attackingColor - color of the enemy pieces
 *
 * @return vector of filtered moves
 */
//cannot step on the same color, cannot jump over pieces, can step on the first of other colors
std::vector<Coordinate> SpecialMovesHandler::filterInvalidMoves(const State& state, std::vector< std::vector<Coordinate> >& abstractMoves, const Color& attackingColor) {
    vector<Coordinate> filtered;

    for (std::size_t i = 0; i < abstractMoves.size(); i++) {
        for (std::size_t j = 0; j < abstractMoves[i].size(); j++) {
            Piece* piece = state.getPiece(abstractMoves[i][j]);
            if (piece == NULL) {
                filtered.push_back(abstractMoves[i][j]);
            } else if(piece->getColor() != attackingColor) {
                filtered.push_back(abstractMoves[i][j]);
                break;
            } else {
                break;
            }
        }
    }
    return filtered;
}

/**
 * @brief SpecialMovesHandler::getSpecialMoves
 *
 * Makes all necessary checks for castling.
 *
 * @param king - king piece
 * @param state - game state
 * @param abstractMoves - possible moves after going through filterInvalidMoves
 * @param kingCoordinate - coordinates of the king
 *
 * @return vector of filtered moves
 */
void SpecialMovesHandler::getSpecialMoves(King *king, const State &state, std::vector<Coordinate> &abstractMoves, Coordinate kingCoordinate) {
    //if king and rook haven't been moved and there are no pieces between them
    for (std::size_t i = 0; i < abstractMoves.size(); i++) {
        Coordinate move = abstractMoves[i];
        //if move is for kingside castling
        if (move.getColumn() == kingCoordinate.getColumn() + 2) {
            Piece* rightRook = state.getPiece(Coordinate(kingCoordinate.getRow(), kingCoordinate.getColumn() + 3));
            //check if position skipped by king is controlled enemy figure
            bool isControlled = CheckChecker::isCellUnderAttack(state,
                                                                    Coordinate(kingCoordinate.getRow(), kingCoordinate.getColumn() + 1),
                                                                    ColorUtils::getOppositeColor(king->getColor()));
            //check if rook has moved or king is in check or isControlled
            if (rightRook == NULL || rightRook->getType() != Piece::ptRook || rightRook->getMoved()
                    || state.getCheckStatusCurrentPlayer() || isControlled) {
                abstractMoves.erase(abstractMoves.begin() + i);
                i--;
            }
        //if move is for queenside castling
        } else if (move.getColumn() == kingCoordinate.getColumn() - 2) {
            Piece* leftRook = state.getPiece(Coordinate(kingCoordinate.getRow(), kingCoordinate.getColumn() - 4));
            Piece* colOne = state.getPiece(Coordinate(kingCoordinate.getRow(), kingCoordinate.getColumn() - 3));
            //check if position skipped by king is controlled enemy figure
            bool isControlled = CheckChecker::isCellUnderAttack(state,
                                                                    Coordinate(kingCoordinate.getRow(),kingCoordinate.getColumn() - 1),
                                                                    ColorUtils::getOppositeColor(king->getColor()));
            //check if rook has moved or king is in check or isControlled
            if (leftRook == NULL || leftRook->getType() != Piece::ptRook || leftRook->getMoved()
                    || state.getCheckStatusCurrentPlayer() || colOne != NULL || isControlled) {
                abstractMoves.erase(abstractMoves.begin() + i);
                i--;
            }
        }
    }
}

/**
 * @brief SpecialMovesHandler::getSpecialMoves
 *
 * Acts as filter for pawn since it cannot take enemy pieces forward
 * and can only move diagonally when taking enemy pieces.
 *
 * @param pawn - pawn piece
 * @param state - game state
 * @param abstractMoves - possible moves of pawn
 * @param pawnCoordinate - coordinates of the pawn
 *
 * @return vector of filtered moves
 */
void SpecialMovesHandler::getSpecialMoves(Pawn *pawn, const State &state, std::vector<Coordinate> &abstractMoves, Coordinate pawnCoordinate) {
    Coordinate move;
    for (std::size_t i = 0; i < abstractMoves.size(); i++) {
        move = abstractMoves[i];
        //if move is diagonal
        if (pawnCoordinate.getColumn() != move.getColumn()) {
            Piece* piece = state.getPiece(move);
            //if cell is empty erase move
            if (piece == NULL) {
                abstractMoves.erase(abstractMoves.begin() + i);
                i--;
            }
          //if move is forward
        } else {
            Piece* piece = state.getPiece(move);
            //if cell is not empty erase move
            if (piece != NULL) {
                abstractMoves.erase(abstractMoves.begin() + i);
                i--;
            }
        }
    }
}

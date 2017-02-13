#include "specialmoveshandler.h"
#include "checkchecker.h"

SpecialMovesHandler::SpecialMovesHandler() {
}

std::vector<Coordinate> SpecialMovesHandler::getValidMoves(const State& state, Coordinate click) {
    Piece* p = state.getPiece(click);
    std::vector< vector<Coordinate> > result = p->getPossibleMoves(click);
    std::vector<Coordinate> moves;
    moves = filterInvalidMoves(state, result, p->getColor());
    switch(p->getType()) {
    case Piece::ptKing :
        getSpecialMoves((King*)p, state, moves, click);
        break;
    case Piece::ptQueen :
        getSpecialMoves((Queen*)p, state, moves);
        break;
    case Piece::ptRook :
        getSpecialMoves((Rook*)p, state, moves);
        break;
    case Piece::ptBishop :
        getSpecialMoves((Bishop*)p, state, moves);
        break;
    case Piece::ptKnight :
        getSpecialMoves((Knight*)p, state, moves);
        break;
    case Piece::ptPawn :
        getSpecialMoves((Pawn*)p, state, moves, click);
        break;
    }

    return moves;
}

// cannot step on the same color, cannot jump over pieces, can step on the first of other colors
std::vector<Coordinate> SpecialMovesHandler::filterInvalidMoves(const State& state, std::vector< std::vector<Coordinate> >& abstractMoves, const Color& attackingColor) {
    vector<Coordinate> filtered;

    for (int i = 0; i < abstractMoves.size(); i++) {
        for (int j = 0; j < abstractMoves[i].size(); j++) {
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

void SpecialMovesHandler::getSpecialMoves(King *king, const State &state, std::vector<Coordinate> &abstractMoves, Coordinate kingCoordinate) {
    // if king and rook haven't been moved and there are no pieces between them
    for (int i = 0; i < abstractMoves.size(); i++) {
        Coordinate move = abstractMoves[i];
        // check right castling
        if (move.getColumn() == kingCoordinate.getColumn() + 2 && !king->getMoved()) {
            // TODO check if the piece pointer is null
            Piece* rightRook = state.getPiece(Coordinate(kingCoordinate.getRow(), kingCoordinate.getColumn() + 3));
            // check if he position the king is skipping is controlled by enemy figure
            bool isControlled = CheckChecker::isPositionUnderAttack(state, Coordinate(kingCoordinate.getRow(), kingCoordinate.getColumn() + 1), ColorUtils::getOppositeColor(king->getColor()));
            // check if rook has moved or king is in check
            if (rightRook == NULL || rightRook->getType() != Piece::ptRook || rightRook->getMoved() || state.getCheckStatusCurrentPlayer() || isControlled) {
                abstractMoves.erase(abstractMoves.begin() + i);
                i--;
            }
        // check left castling
        } else if (move.getColumn() == kingCoordinate.getColumn() - 2 && !king->getMoved()) {
            Piece* leftRook = state.getPiece(Coordinate(kingCoordinate.getRow(), kingCoordinate.getColumn() - 4));
            Piece* colOne = state.getPiece(Coordinate(kingCoordinate.getRow(), kingCoordinate.getColumn() - 3));
            // check if he position the king is skipping is controlled by enemy figure
            bool isControlled = CheckChecker::isPositionUnderAttack(state, Coordinate(kingCoordinate.getRow(), kingCoordinate.getColumn() - 1), ColorUtils::getOppositeColor(king->getColor()));
            // check if rook has moved or king is in check or if column next to rook is free
            if (leftRook == NULL || leftRook->getType() != Piece::ptRook || leftRook->getMoved() || state.getCheckStatusCurrentPlayer() || colOne != NULL || isControlled) {
                abstractMoves.erase(abstractMoves.begin() + i);
                i--;
            }
        }
    }
}

void SpecialMovesHandler::getSpecialMoves(Queen *queen, const State &state, std::vector<Coordinate> &abstractMoves) {
    // TO-DO
}

void SpecialMovesHandler::getSpecialMoves(Rook *rook, const State &state, std::vector<Coordinate> &abstractMoves) {
    // TO-DO
}

void SpecialMovesHandler::getSpecialMoves(Bishop *bishop, const State &state, std::vector<Coordinate> &abstractMoves) {
    // TO-DO
}

void SpecialMovesHandler::getSpecialMoves(Knight *knight, const State &state, std::vector<Coordinate> &abstractMoves) {
    // TO-DO
}

void SpecialMovesHandler::getSpecialMoves(Pawn *pawn, const State &state, std::vector<Coordinate> &abstractMoves, Coordinate pawnCoordinate) {
    Coordinate move;
    //for every move
    for (int i = 0; i < abstractMoves.size(); i++) {
        move = abstractMoves[i];
        //if move is diagonal
        if (pawnCoordinate.getColumn() != move.getColumn()) {
            Piece* piece = state.getPiece(move);
            if (piece == NULL) {
                abstractMoves.erase(abstractMoves.begin() + i);
                i--;
            }
          //if move is one forward
        } else {
            Piece* piece = state.getPiece(move);
            if (piece != NULL) {
                abstractMoves.erase(abstractMoves.begin() + i);
                i--;
            }
        }
    }
}

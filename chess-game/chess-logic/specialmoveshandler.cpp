#include "specialmoveshandler.h"

SpecialMovesHandler::SpecialMovesHandler() {
}

std::vector<Coordinate> SpecialMovesHandler::getValidMoves(const State& state, Coordinate click) {
    Piece* p = state.getPiece(click);
    std::vector< vector<Coordinate> > result = p->getPossibleMoves(click);
    std::vector<Coordinate> moves = filterInvalidMoves(state, result, p->getColor());

    switch(p->getType()) {
    case Piece::ptKing :
        getSpecialMoves((King*)p, state, moves);
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
        getSpecialMoves((Pawn*)p, state, moves);
        break;
    }

    return moves;
}

std::vector<Coordinate> SpecialMovesHandler::filterInvalidMoves(const State& state, std::vector< std::vector<Coordinate> >& abstractMoves, const Color& attackingColor) {
    vector<Coordinate> filtered;
/*
    for (int i=0; i<abstractMoves.size(); i++) {
        Piece* piece = state.getPiece(abstractMoves[i]);
        if (piece == nullptr || piece->getColor() != attackingColor) {
            filtered.push_back(abstractMoves[i]);
        }
    }
*/

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

void SpecialMovesHandler::getSpecialMoves(King *king, const State &state, std::vector<Coordinate> &abstractMoves) {
    // TO-DO
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

void SpecialMovesHandler::getSpecialMoves(Pawn *pawn, const State &state, std::vector<Coordinate> &abstractMoves) {
    // TO-DO
}

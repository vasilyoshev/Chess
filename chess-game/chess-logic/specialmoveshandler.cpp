#include "specialmoveshandler.h"

SpecialMovesHandler::SpecialMovesHandler() {
}

std::vector<Coordinate> SpecialMovesHandler::getValidMoves(const State& state, Coordinate click) {
    Piece* p = state.getPiece(click);
    std::vector< vector<Coordinate> > result = p->getPossibleMoves(click);
    std::vector<Coordinate> moves;
    if (p->getType() != Piece::ptPawn)
        moves = filterInvalidMoves(state, result, p->getColor());
    else
        moves = filterPawn(state, result, p->getColor());
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

std::vector<Coordinate> SpecialMovesHandler::filterPawn(const State& state, std::vector< std::vector<Coordinate> > & abstractMoves, const Color& attackingColor) {
    vector<Coordinate> filtered;

    for (int i = 0; i < abstractMoves.size(); i++) {
        filtered.push_back(abstractMoves[i][0]);
    }

    return filtered;
}

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
    int size = abstractMoves.size();
    if (size == 0) return;
    bool bothHorizontal = abstractMoves[0].getColumn() == abstractMoves[1].getColumn();

    Coordinate first = abstractMoves[0];
    Coordinate second = abstractMoves[1];

    if (size == 2 && bothHorizontal) {
        if (state.getPiece(first) != NULL)
            abstractMoves.clear();
        else if (state.getPiece(second) != NULL)
            abstractMoves.pop_back();
    } else if (size == 2) {
        //if first element is forward
        if (first.getColumn() == second.getColumn() - 1 || first.getColumn() == second.getColumn() + 1) {
            if (state.getPiece(first) != NULL)
                abstractMoves.erase(abstractMoves.begin());
            if (state.getPiece(second) == NULL)
                abstractMoves.pop_back();
        } else {
            if (state.getPiece(first) == NULL)
                abstractMoves.erase(abstractMoves.begin());
            if (state.getPiece(second) == NULL)
                        abstractMoves.pop_back();
        }
    }

    if (size == 3 && bothHorizontal) {
        if (state.getPiece(first) != NULL)
            abstractMoves.clear();
        else if (state.getPiece(second) != NULL)
            abstractMoves.erase(abstractMoves.begin() + 1);

        if (state.getPiece(abstractMoves[abstractMoves.size() - 1]) == NULL)
            abstractMoves.pop_back();
    } else if (size == 3) {
        if (state.getPiece(first) != NULL)
            abstractMoves.erase(abstractMoves.begin());
        if (state.getPiece(abstractMoves[abstractMoves.size() - 2]) == NULL)
            abstractMoves.erase(abstractMoves.end() - 2);
        if (state.getPiece(abstractMoves[abstractMoves.size() - 1]) == NULL)
            abstractMoves.pop_back();
    }

    if (size == 4) {
        if (state.getPiece(abstractMoves[0]) != NULL) {
            abstractMoves.erase(abstractMoves.begin(), abstractMoves.begin() + 2);
        } else if (state.getPiece(abstractMoves[1]) != NULL) {
            abstractMoves.erase(abstractMoves.begin() + 1);
        }
        if (state.getPiece(abstractMoves[abstractMoves.size() - 2]) == NULL)
            abstractMoves.erase(abstractMoves.end() - 2);
        if (state.getPiece(abstractMoves[abstractMoves.size() - 1]) == NULL)
            abstractMoves.pop_back();
    }
}

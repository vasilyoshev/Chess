#include "specialmoveshandler.h"

SpecialMovesHandler::SpecialMovesHandler()
{
}

std::vector<Coordinate> SpecialMovesHandler::getValidMoves(const State &state, Coordinate click)
{
    Piece *p = state.getPiece(click);
    std::vector<Coordinate> result = p->getPossibleMoves(click);

    filterInvalidMoves(state,result);

    switch(p->getType()) {
    case Piece::ptKing :
        getSpecialMoves((King*)p, state, result);
        break;
    case Piece::ptQueen :
        getSpecialMoves((Queen*)p, state, result);
        break;
    case Piece::ptRook :
        getSpecialMoves((Rook*)p, state, result);
        break;
    case Piece::ptBishop :
        getSpecialMoves((Bishop*)p, state, result);
        break;
    case Piece::ptKnight :
        getSpecialMoves((Knight*)p, state, result);
        break;
    case Piece::ptPawn :
        getSpecialMoves((Pawn*)p, state, result);
        break;
    }

    return result;
}

void SpecialMovesHandler::filterInvalidMoves(const State &state, std::vector<Coordinate> &abstractMoves)
{
    std::vector<Coordinate>::iterator it = abstractMoves.begin();
    for(;it!=abstractMoves.end();) {
        if(state.getPiece(*it)!=nullptr) {
            it = abstractMoves.erase(it);
        } else {
            ++it;
        }
    }
}

void SpecialMovesHandler::getSpecialMoves(King *king, const State &state, std::vector<Coordinate> &abstractMoves)
{
    // TO-DO
}

void SpecialMovesHandler::getSpecialMoves(Queen *queen, const State &state, std::vector<Coordinate> &abstractMoves)
{
    // TO-DO
}

void SpecialMovesHandler::getSpecialMoves(Rook *rook, const State &state, std::vector<Coordinate> &abstractMoves)
{
    // TO-DO
}

void SpecialMovesHandler::getSpecialMoves(Bishop *bishop, const State &state, std::vector<Coordinate> &abstractMoves)
{
    // TO-DO
}

void SpecialMovesHandler::getSpecialMoves(Knight *knight, const State &state, std::vector<Coordinate> &abstractMoves)
{
    // TO-DO
}

void SpecialMovesHandler::getSpecialMoves(Pawn *pawn, const State &state, std::vector<Coordinate> &abstractMoves)
{
    // TO-DO
}

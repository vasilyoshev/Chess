
#include "ai/ai.h"
#include <vector>

#include "piece.h"
#include "rook.h"
#include "king.h"
#include "pawn.h"
#include "queen.h"
#include "bishop.h"
#include "knight.h"


Ai::Ai()
{
    //
}

Coordinate Ai::getAllRandomValidTurns(State state, Color color)
{
    vector<Coordinate> allAiMoves = controller.getAiTurn(state);
    vector<vector<Coordinate> > validAiMoves;


    for (int i = 0; i < allAiMoves.size(); i++){

    column = allAiMoves[i].getColumn(); // gets Column Coordinate
    row = allAiMoves[i].getRow();       // get row coordinate
    Piece* aiPiece = state.getBoard()[row][column].getPiece(); // piece position & type

    if (Piece::ptKing == aiPiece->getType()){               //king

        Coordinate kingPosition = Coordinate(row, column);
        King king = King(color);
        validAiMoves = king.getPossibleMoves(kingPosition);
            if (validAiMoves.empty()){
                break;
            }
    }
    else if (Piece::ptRook == aiPiece->getType() ){ // if piece is a Rook type

                Coordinate rookPosition = Coordinate(row, column);
                Rook rook = Rook(color);
                validAiMoves = rook.getPossibleMoves(rookPosition);
                    if (validAiMoves.empty()){
                        break;
                    }
     }
     else if (Piece::ptQueen == aiPiece->getType()){ // if a piece is a Queen type

            Coordinate queenPosition = Coordinate(row, column);
            Queen queen = Queen(color);
            validAiMoves = queen.getPossibleMoves(queenPosition);
                if (validAiMoves.empty()){
                    break;
                }
     }
     else if (Piece::ptBishop ==  aiPiece->getType()){  // if the piece is a Bishop

        Coordinate bishopPosition = Coordinate(row, column);
        Bishop bishop = Bishop(color);
        validAiMoves = bishop.getPossibleMoves(bishopPosition); //
                if (validAiMoves.empty()){
                    break;
                }
     }
     else if (Piece::ptKnight == aiPiece->getType()){ // knight

        Coordinate knightPosition = Coordinate(row, column);
        Knight knight = Knight(color);
        validAiMoves = knight.getPossibleMoves(knightPosition);
                if (validAiMoves.empty()){
                    break;
                }
     }
     else if (Piece::ptPawn == aiPiece->getType()){ // pawn

        Coordinate pawnPosition = Coordinate(row, column);
        Pawn pawn = Pawn(color);
        validAiMoves = pawn.getPossibleMoves(pawnPosition);
                if (validAiMoves.empty()){
                    break;
               }
        }



     } // end of FOR

    int vectorSize = validAiMoves.size();
    int r = rand() % vectorSize;

    vector<Coordinate> finalCoordinateList = validAiMoves[r];

    int finalListSize = finalCoordinateList.size();
    int t = rand() % finalListSize;

    row = finalCoordinateList[t].getRow();
    column = finalCoordinateList[t].getColumn();

    Coordinate targetCoordinates = Coordinate(row, column);



    return targetCoordinates;

}

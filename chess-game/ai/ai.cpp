
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

vector<Coordinate> Ai::getAllRandomValidTurns(State state, Color color)
{
    vector<Coordinate> allAiMoves = controller.getAiTurn(state);
    vector<vector<Coordinate> > validAiMoves;
    int sourceColumn;
    int sourceRow;

    for (int i = 0; i < allAiMoves.size(); i++){

    column = allAiMoves[i].getColumn(); // gets Column Coordinate
    row = allAiMoves[i].getRow();       // get row coordinate

    sourceColumn = column;
    sourceRow = row;

    Coordinate piecePosition2 = Coordinate(row, column);
    Piece* aiPiece = state.getPiece(piecePosition2);      // gets the piece from the coordinates given

    if (Piece::ptKing == aiPiece->getType()){               //Checks to see if the piece is a King

        Coordinate kingPosition = Coordinate(row, column);
        King king = King(color);
        validAiMoves = king.getPossibleMoves(kingPosition);
            if (validAiMoves.empty()){
                break;
            }
    }
    else if (Piece::ptRook == aiPiece->getType() ){ // Checks to see if the piece is aRook type

                Coordinate rookPosition = Coordinate(row, column);
                Rook rook = Rook(color);
                validAiMoves = rook.getPossibleMoves(rookPosition);
                    if (validAiMoves.empty()){
                        break;
                    }
     }
     else if (Piece::ptQueen == aiPiece->getType()){ // Checks to see if the piece is a Queen type

            Coordinate queenPosition = Coordinate(row, column);
            Queen queen = Queen(color);
            validAiMoves = queen.getPossibleMoves(queenPosition);
                if (validAiMoves.empty()){
                    break;
                }
     }
     else if (Piece::ptBishop ==  aiPiece->getType()){  // Checks to see if the piece is a Bishop

        Coordinate bishopPosition = Coordinate(row, column);
        Bishop bishop = Bishop(color);
        validAiMoves = bishop.getPossibleMoves(bishopPosition); //
                if (validAiMoves.empty()){
                    break;
                }
     }
     else if (Piece::ptKnight == aiPiece->getType()){ //Checks to see if the piece is a Pnight

        Coordinate knightPosition = Coordinate(row, column);
        Knight knight = Knight(color);
        validAiMoves = knight.getPossibleMoves(knightPosition);
                if (validAiMoves.empty()){
                    break;
                }
     }
     else if (Piece::ptPawn == aiPiece->getType()){ // Checks to see if the piece is a Pawn

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
    // Takes a random vector from the two dimensional vector.
    int finalListSize = finalCoordinateList.size();
    int t = rand() % finalListSize;
    // Takes a random coordinate from the finalCoordinateList vector
    row = finalCoordinateList[t].getRow();  // gets row of the Coordinate
    column = finalCoordinateList[t].getColumn(); // gets column of the Coordinate

    Coordinate targetCoordinates = Coordinate(row, column);

    //

    Coordinate sourceCoordinates = Coordinate(sourceRow, sourceColumn);

    vector<Coordinate> sourceTarget;
    sourceTarget[0] = sourceCoordinates;
    sourceTarget[1] = targetCoordinates;




    return sourceTarget; // returns the source and target coordinates for the AI

}

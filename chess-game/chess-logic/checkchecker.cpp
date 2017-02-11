#include <vector>

#include "state.h"
#include "piece.h"
#include "color.h"
#include "coordinate.h"
#include "checkchecker.h"
#include "specialmoveshandler.h"

Color CheckChecker::getOtherPlayerColor(const State& state) {
    if (state.getCurrentPlayer()->getColor() == cBlack) {
        return cWhite;
    }
    return cBlack;
}

bool CheckChecker::checkForCheck(const State& state) {
    Coordinate king = locateCurrentPlayerKing(state);
    Color otherPlayerColor = getOtherPlayerColor(state);

    return checkForCheck(state, king, otherPlayerColor);
}

bool CheckChecker::checkForCheckmate(const State& state) {
    Color currentPlayerColor = state.getCurrentPlayer()->getColor();

    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int column = 0; column < BOARD_SIZE; column++) {
            Piece* piece = state.getBoard()[row][column].getPiece();

            if (piece != NULL && piece->getColor() == currentPlayerColor) {
                Coordinate coordinate = Coordinate(row, column);
                if (filterCheckMoves(state, SpecialMovesHandler::getValidMoves(state, coordinate), coordinate).size() > 0) {
                    return false;
                }
            }
        }
    }

    return true;
}

bool CheckChecker::checkForCheck(const State& state, const Coordinate& position, const Color& attackingColor) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int column = 0; column < BOARD_SIZE; column++) {
            Piece* piece = state.getBoard()[row][column].getPiece();

            if (piece != NULL && piece->getColor() == attackingColor) {
                vector<Coordinate> attackingPositions = SpecialMovesHandler::getValidMoves(state, Coordinate(row, column));

                for (int i=0; i<attackingPositions.size(); i++) {
                    if (attackingPositions[i] == position) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

Coordinate CheckChecker::locateCurrentPlayerKing(const State& state) {
    vector< vector<Cell> > board  = state.getBoard();

    for (int row = 0; row < 8; row++) {
        for (int column = 0; column < 8; column++) {
            Cell currentCell = board[row][column];
            Piece* piece = currentCell.getPiece();

            if (piece != NULL && piece->getType() == Piece::ptKing && piece->getColor() == state.getCurrentPlayer()->getColor()) {
                return Coordinate(row, column);
            }
        }
    }
    // TODO throw an exception?
}

vector<Coordinate> CheckChecker::filterCheckMoves(const State& state,
                                                  vector<Coordinate> possibleMoves,
                                                  const Coordinate& source) {
    vector<Coordinate> filtered;

    for (int i = 0; i < possibleMoves.size(); i++) {
        Coordinate target = possibleMoves[i];
        State afterMove = State(state);
        Piece* sourcePiece = afterMove.getPiece(source);
        Piece* targetPiece = afterMove.getPiece(target);
        delete targetPiece;
        afterMove.setPiece(nullptr, source);
        afterMove.setPiece(sourcePiece, target);

        if (!checkForCheck(afterMove)) {
            filtered.push_back(possibleMoves[i]);
        }
    }

    return filtered;
}

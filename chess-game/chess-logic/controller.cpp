#include "controller.h"
#include "piece.h"
#include "checkchecker.h"

Controller::Controller() {
    initState();
}

void Controller::initState() {
    initPieces();
    initPlayers();
}

void Controller::initPieces() {
    setMajorPieces(0, cBlack);
    setPawnPieces(1, cBlack);
    setPawnPieces(6, cWhite);
    setMajorPieces(7, cWhite);
}

void Controller::setPawnPieces(int row, Color color) {
    for(int column = 0; column < 8; column++) {
        state.setPiece(new Pawn(color), Coordinate(row, column));
    }
}

void Controller::setMajorPieces(int row, Color color) {
    state.setPiece(new Rook(color), Coordinate(row, 0));
    state.setPiece(new Knight(color), Coordinate(row, 1));
    state.setPiece(new Bishop(color), Coordinate(row, 2));
    state.setPiece(new Queen(color), Coordinate(row, 3));
    state.setPiece(new King(color), Coordinate(row, 4));
    state.setPiece(new Bishop(color), Coordinate(row, 5));
    state.setPiece(new Knight(color), Coordinate(row, 6));
    state.setPiece(new Rook(color), Coordinate(row, 7));
}

vector<Coordinate> Controller::getValidMoves(Coordinate click) {
    if(!click.isInBoard()) {
        return vector<Coordinate>();
    }

    return CheckChecker::filterCheckMoves(state, SpecialMovesHandler::getValidMoves(state, click), click);
}

const State& Controller::getState() {
    return state;
}

void Controller::movePiece(Coordinate source, Coordinate target) {
    Piece* sourcePiece = state.getPiece(source);
    Piece* targetPiece = state.getPiece(target);
    delete targetPiece;
    state.setPiece(sourcePiece, target);
    state.setPiece(nullptr, source);

    state.nextPlayer();
    if (CheckChecker::checkForCheck(state)) {
        state.getCurrentPlayer()->setInCheck(true);
        state.getCurrentPlayer()->setInCheckmate(CheckChecker::checkForCheckmate(state));
        if (CheckChecker::checkForCheckmate(state)) {
            exit(0);
        }
    }
}

void Controller::initPlayers() {
    state.initPlayer1("Vlado", cBlack);
    state.initPlayer2("Vasko", cWhite);
}

void Controller::setFirstPlayerColor(Color color) {
    // TO-DO
}

void Controller::setGameType(TGameType gameType) {
    // TO-DO
}

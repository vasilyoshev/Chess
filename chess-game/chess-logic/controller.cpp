#include "controller.h"
#include "piece.h"
#include "checkchecker.h"

Controller::Controller() {
    initState();
}

void Controller::initState() {
    initPieces();
//    initPlayers();
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

bool Controller::isLeftCastle(Piece::PieceType pieceType, Coordinate source, Coordinate target) {
    return pieceType==Piece::PieceType::ptKing && target.getColumn()==source.getColumn()-2;
}

bool Controller::isRightCastle(Piece::PieceType pieceType, Coordinate source, Coordinate target) {
    return pieceType==Piece::PieceType::ptKing && target.getColumn()==source.getColumn()+2;
}

void Controller::movePiece(Coordinate source, Coordinate target) {
    Piece* sourcePiece = state.getPiece(source);

    if(isLeftCastle(sourcePiece->getType(), source, target)) {
        Coordinate rookSource = Coordinate(target.getRow(), target.getColumn() - 2);
        Coordinate rookTarget = Coordinate(target.getRow(), target.getColumn() + 1);
        Piece* rook = state.getPiece(rookSource);

        state.setPiece(sourcePiece, target);
        state.setPiece(nullptr, source);
        state.setPiece(rook, rookTarget);
        state.setPiece(nullptr, rookSource);

        sourcePiece->setMoved();
        rook->setMoved();
        changePlayer();
    } else if(isRightCastle(sourcePiece->getType(), source, target)) {
        Coordinate rookSource = Coordinate(target.getRow(), target.getColumn() + 1);
        Coordinate rookTarget = Coordinate(target.getRow(), target.getColumn() - 1);
        Piece* rook = state.getPiece(rookSource);

        state.setPiece(sourcePiece, target);
        state.setPiece(nullptr, source);
        state.setPiece(rook, rookTarget);
        state.setPiece(nullptr, rookSource);

        sourcePiece->setMoved();
        rook->setMoved();
        changePlayer();
    } else {
        Piece* targetPiece = state.getPiece(target);
        delete targetPiece;
        state.setPiece(sourcePiece, target);
        state.setPiece(nullptr, source);

        sourcePiece->setMoved();

        state.getCurrentPlayer()->setInCheck(false);

        checkAndSetPawnPromotion(sourcePiece, target);
        if(!state.isInPownPromotion()) {
            changePlayer();
        }
    }
}

void Controller::checkAndSetPawnPromotion(Piece* sourcePiece, Coordinate& pieceCoordinate) {
    if (sourcePiece->getType() == Piece::PieceType::ptPawn &&
            ((sourcePiece->getColor() == cWhite && pieceCoordinate.getRow() == 0) ||
             (sourcePiece->getColor() == cBlack && pieceCoordinate.getRow() == 7))) {
        state.setInPownPromotion(true);
        state.setPownInPromotionCoordinates(&pieceCoordinate);
    }
}

void Controller::promotePown(Piece::PieceType pieceType) {
    Coordinate* pownCoordinate = state.getPownInPromotionCoordinates();

    Piece* pawn = state.getPiece(*pownCoordinate);
    Color pawnColor = pawn->getColor();
    delete pawn;

    if (pieceType == Piece::PieceType::ptQueen) {
        state.setPiece(new Queen(pawnColor), *pownCoordinate);
    } else if (pieceType == Piece::PieceType::ptKnight) {
        state.setPiece(new Knight(pawnColor), *pownCoordinate);
    } else if (pieceType == Piece::PieceType::ptRook) {
        state.setPiece(new Rook(pawnColor), *pownCoordinate);
    } else if (pieceType == Piece::PieceType::ptBishop) {
        state.setPiece(new Bishop(pawnColor), *pownCoordinate);
    }

    state.setInPownPromotion(false);
    changePlayer();
}

bool Controller::isInPownPromotion(){
    return state.isInPownPromotion();
}

void Controller::changePlayer() {
    state.nextPlayer();
    if (CheckChecker::checkForCheck(state)) {
        state.getCurrentPlayer()->setInCheck(true);
        state.getCurrentPlayer()->setInCheckmate(CheckChecker::checkForCheckmate(state));
    }
}

void Controller::initPlayers() {
    //state.initPlayer1("Vlado", cBlack);
    //state.initPlayer2("Vasko", cWhite);
}

void Controller::setFirstPlayer(string name, Color color) {
    state.initPlayer1(name,color);
}

void Controller::setSecondPlayer(string name, Color color) {
    state.initPlayer2(name,color);
}

void Controller::setGameType(TGameType gameType) {
    state.initGameType(gameType);
}

void Controller::initStartingPlayer() {
    if(state.getCurrentPlayer()->getColor() != cWhite) {
        state.nextPlayer();
    }
}

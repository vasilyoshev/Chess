#include "state.h"

State::State() {
    board.resize(BOARD_SIZE, vector<Cell>(BOARD_SIZE));
    initPieces();

    currentPlayerIndex = 0;
    currentPlayer = &players[currentPlayerIndex];
    inPawnPromotion = false;
    pawnInPromotionCoordinates = NULL;
}

State::~State() {
    if (pawnInPromotionCoordinates != NULL) {
        delete pawnInPromotionCoordinates;
    }
}

State::State(const State& state) {
    board.resize(BOARD_SIZE, vector<Cell>(BOARD_SIZE));
    for(int row = 0; row < BOARD_SIZE; row++) {
        for(int column = 0; column < BOARD_SIZE; column++) {
            board[row][column] = Cell(state.getBoard()[row][column]);
        }
    }

    currentPlayerIndex = state.currentPlayerIndex;
    players[0] = Player(state.players[0]);
    players[1] = Player(state.players[1]);
    currentPlayer = &players[currentPlayerIndex];
    inPawnPromotion = state.isInPownPromotion();
    pawnInPromotionCoordinates = NULL;
}


void State::setPawnPieces(int row, Color color) {
    for(int column = 0; column < 8; column++) {
        setPiece(new Pawn(color), Coordinate(row, column));
    }
}

void State::setMajorPieces(int row, Color color) {
    setPiece(new Rook(color), Coordinate(row, 0));
    setPiece(new Knight(color), Coordinate(row, 1));
    setPiece(new Bishop(color), Coordinate(row, 2));
    setPiece(new Queen(color), Coordinate(row, 3));
    setPiece(new King(color), Coordinate(row, 4));
    setPiece(new Bishop(color), Coordinate(row, 5));
    setPiece(new Knight(color), Coordinate(row, 6));
    setPiece(new Rook(color), Coordinate(row, 7));
}

void State::initPieces() {
    setMajorPieces(0, cBlack);
    setPawnPieces(1, cBlack);
    setPawnPieces(6, cWhite);
    setMajorPieces(7, cWhite);
}

void State::setPiece(Piece* piece, Coordinate coordinate) {
    if(!coordinate.isInBoard()) {
        return; // maybe exception or log error/warn message
    }

    board[coordinate.getRow()][coordinate.getColumn()].setPiece(piece);
}

Piece* State::getPiece(Coordinate coordinate) const {
    if(!coordinate.isInBoard()) {
        return nullptr; // maybe exception or log error/warn message
    }

    return board[coordinate.getRow()][coordinate.getColumn()].getPiece();
}

const vector< vector<Cell> >& State::getBoard() const {
    return board;
}

Player* State::getCurrentPlayer() const {
    return currentPlayer;
}

void State::nextPlayer() {
    currentPlayerIndex = (currentPlayerIndex + 1) % 2;
    currentPlayer = &players[currentPlayerIndex];
}

void State::initPlayer1(string name, Color color) {
    players[0].setName(name);
    players[0].setColor(color);
}

void State::initPlayer2(string name, Color color) {
    players[1].setName(name);
    players[1].setColor(color);
}

void State::setCheckStatusCurrentPlayer(bool inCheck) {
    currentPlayer->setInCheck(inCheck);
}

bool State::getCheckStatusCurrentPlayer() const {
    return currentPlayer->isInCheck();
}

bool State::isInPownPromotion() const {
    return inPawnPromotion;
}

bool State::setInPawnPromotion(bool inPownPromotion) {
    if (!inPownPromotion && pawnInPromotionCoordinates != NULL) {
        delete pawnInPromotionCoordinates;
    }
    this->inPawnPromotion = inPownPromotion;
}

void State::initGameType(TGameType gameType) {
    this->gameType = gameType;
}

Coordinate* State::getPawnInPromotionCoordinates() {
    return pawnInPromotionCoordinates;
}

void State::setPawnInPromotionCoordinates(Coordinate* pawnInPromotionCoordinates) {
    this->pawnInPromotionCoordinates = pawnInPromotionCoordinates;
}

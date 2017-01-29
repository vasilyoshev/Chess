#include "state.h"

State::State() {
    board.resize(BOARD_SIZE, vector<Cell>(BOARD_SIZE));

    currentPlayerIndex = 0;
    currentPlayer = &players[currentPlayerIndex];
    inPownPromotion = false;
    pownInPromotionCoordinates = NULL;
}

State::~State() {
    if (pownInPromotionCoordinates != NULL) {
        delete pownInPromotionCoordinates;
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
    inPownPromotion = state.isInPownPromotion();
    pownInPromotionCoordinates = NULL;
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
    return inPownPromotion;
}

bool State::setInPownPromotion(bool inPownPromotion) {
    if (!inPownPromotion && pownInPromotionCoordinates != NULL) {
        delete pownInPromotionCoordinates;
    }
    this->inPownPromotion = inPownPromotion;
}

void State::initGameType(TGameType gameType) {
    this->gameType = gameType;
}

Coordinate* State::getPownInPromotionCoordinates() {
    return pownInPromotionCoordinates;
}

void State::setPownInPromotionCoordinates(Coordinate* pownInPromotionCoordinates) {
    this->pownInPromotionCoordinates = pownInPromotionCoordinates;
}

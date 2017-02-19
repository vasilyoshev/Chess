#include "state.h"

/**
 * @brief State::State
 * Default constructor intializes the state of the chess game.
 * Creates and sets all pieces on the board.
 */
State::State() {
    board.resize(BOARD_SIZE, vector<Cell>(BOARD_SIZE));
    initPieces(); // creating the pieces

    currentPlayerIndex = 0;
    currentPlayer = &players[currentPlayerIndex];
    inPawnPromotion = false;
}

/**
 * @brief State::State
 * Copy constructor
 *
 * @param state the state that has to be copied
 */
State::State(const State& state) {
    board.resize(BOARD_SIZE, vector<Cell>(BOARD_SIZE));
    for(int row = 0; row < BOARD_SIZE; row++) {
        for(int column = 0; column < BOARD_SIZE; column++) {
            board[row][column] = Cell(state.board[row][column]); // copying every cell
        }
    }

    currentPlayerIndex = state.currentPlayerIndex;
    players[0] = Player(state.players[0]);
    players[1] = Player(state.players[1]);
    currentPlayer = &players[currentPlayerIndex];
    inPawnPromotion = state.isInPawnPromotion();
    pawnInPromotionCoordinates = Coordinate(state.getPawnInPromotionCoordinates());
}

/**
 * @brief State::setPawnPieces
 * Sets pawn pieces on the entire row.
 *
 * @param row the row which has to be filled with pawns
 * @param color the color of the pawns
 */
void State::setPawnPieces(int row, Color color) {
    for(int column = 0; column < 8; column++) {
        setPiece(new Pawn(color), Coordinate(row, column));
    }
}

/**
 * @brief State::setMajorPieces
 * Sets major pieces on the entire row
 *
 * @param row the row which has to be filled with major pieces
 * @param color the color of the pieces
 */
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

/**
 * @brief State::initPieces
 * Sets the pieces on the board
 */
void State::initPieces() {
    setMajorPieces(0, cBlack);
    setPawnPieces(1, cBlack);
    setPawnPieces(6, cWhite);
    setMajorPieces(7, cWhite);
}

/**
 * @brief State::setPiece
 * Sets a piece on the provided coordinates.
 * The caller is responsible for deleting any piece currently on the cell.
 *
 * @param piece the piece to set
 * @param coordinate the coordinates on which the piece should be placed
 */
void State::setPiece(Piece* piece, Coordinate coordinate) {
    if(!coordinate.isInBoard()) {
        return; // cannot place a piece outside the board
    }

    board[coordinate.getRow()][coordinate.getColumn()].setPiece(piece);
}

/**
 * @brief State::getPiece
 * Returns the piece on the provided coordinate
 *
 * @param coordinate the provided coordinate
 * @return the piece which is on the provided coordinate, nullptr if there is no piece on that coordinate
 */
Piece* State::getPiece(Coordinate coordinate) const {
    if(!coordinate.isInBoard()) {
        return nullptr; // no pieces outside the board
    }

    return board[coordinate.getRow()][coordinate.getColumn()].getPiece();
}

/**
 * @brief State::getCurrentPlayer
 * Returns a reference to the current player
 *
 * @return a reference to the current player
 */
Player* State::getCurrentPlayer() const {
    return currentPlayer;
}

/**
 * @brief State::nextPlayer
 * Changes the current player to the other player
 */
void State::nextPlayer() {
    currentPlayerIndex = (currentPlayerIndex + 1) % 2;
    currentPlayer = &players[currentPlayerIndex];
}

/**
 * @brief State::initPlayer1
 * Initializes player one
 *
 * @param name the name of player one
 * @param color the color of player two
 */
void State::setPlayer1(string name, Color color) {
    players[0].setName(name);
    players[0].setColor(color);
}

/**
 * @brief State::initPlayer2
 * Initializes player two
 *
 * @param name the name of player two
 * @param color the color of player two
 */
void State::setPlayer2(string name, Color color) {
    players[1].setName(name);
    players[1].setColor(color);
}

/**
 * @brief State::getCheckStatusCurrentPlayer
 * Returns the check status for the current player
 *
 * @return true if the current player is in check, false otherwise
 */
bool State::getCheckStatusCurrentPlayer() const {
    return currentPlayer->isInCheck();
}

/**
 * @brief State::isInPawnPromotion
 * Returns true if there is a pawn in promotion
 *
 * @return true if there is a pawn in promotion, false otherwise
 */
bool State::isInPawnPromotion() const {
    return inPawnPromotion;
}

/**
 * @brief State::setInPawnPromotion
 * Sets the flag inPawnPromotion used to indicate if there is a pawn in promotion
 *
 * @param inPownPromotion the flag to set
 */
void State::setInPawnPromotion(bool inPownPromotion) {
    this->inPawnPromotion = inPownPromotion;
}

/**
 * @brief State::setGameType
 * Sets the game type
 *
 * @param gameType the game type to set
 */
void State::setGameType(TGameType gameType) {
    this->gameType = gameType;
}

/**
 * @brief State::getGameType
 * Returns the type of the game.
 *
 * @return the type of the game.
 */
TGameType State::getGameType() {
    return this->gameType;
}

/**
 * @brief State::getPawnInPromotionCoordinates
 * Returns the coordinates of the pawn in promotion
 *
 * @return the coordinate of the pawn in promotion if there is no pawn in promotion the coordinates will be -1 -1
 */
Coordinate State::getPawnInPromotionCoordinates() const {
    return pawnInPromotionCoordinates;
}

/**
 * @brief State::setPawnInPromotionCoordinates
 * Sets the coordinate of the pawn in promotion
 *
 * @param pawnInPromotionCoordinates the coordinates to set
 */
void State::setPawnInPromotionCoordinates(Coordinate pawnInPromotionCoordinates) {
    this->pawnInPromotionCoordinates = pawnInPromotionCoordinates;
}

#ifndef COORDINATE_H
#define COORDINATE_H

/**
 * @brief The Coordinate class wraps row and column coordinates
 */
class Coordinate {
private:
    int row;
    int column;

public:
    Coordinate();
    Coordinate(int row, int column);

    int getRow() const;
    int getColumn() const;
    bool isInBoard() const;

    bool operator==(const Coordinate &other);
    void operator=(const Coordinate &other);
};

#endif // COORDINATE_H

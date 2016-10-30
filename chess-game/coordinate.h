#ifndef COORDINATE_H
#define COORDINATE_H


class Coordinate
{
private:
    int row;
    int column;
public:
    Coordinate(int row, int column);

    int getRow() const;
    int getColumn() const;
};

#endif // COORDINATE_H

#ifndef AI_H
#define AI_H

#include <vector>
#include <QString>


class Ai{

    private:

    // Controller controller; //error here

    void getRandomTurn();
    void getRandomValidPiece();
    void getAllRandomValidTurns();

    public:

    Ai();
    // Ai(Controller controller, Color color); //error here

    void getNextAiTurn();
    void getAiTurn();


};

#endif // AI_H



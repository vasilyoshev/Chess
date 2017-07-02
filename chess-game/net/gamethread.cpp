#include "gamethread.h"

GameThread::GameThread(QTcpSocket *player1, QTcpSocket player2, QObject *parent) : QThread(parent), player1(player1), player2(player2)
{
}

void GameThread::run()
{

}

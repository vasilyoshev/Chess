#ifndef GAMETHREAD_H
#define GAMETHREAD_H

#include <QThread>
#include <QTcpSocket>

class GameThread : public QThread
{
    Q_OBJECT
public:
    GameThread();

protected:
    QTcpSocket player1;
    QTcpSocket player2;
};

#endif // GAMETHREAD_H

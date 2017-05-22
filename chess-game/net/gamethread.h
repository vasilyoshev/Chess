#ifndef GAMETHREAD_H
#define GAMETHREAD_H

#include <QThread>


class GameThread : public QThread
{
    Q_OBJECT
public:
    GameThread();
};

#endif // GAMETHREAD_H

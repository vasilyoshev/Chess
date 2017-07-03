#include "server.h"
#include "thread.h"
#include <stdlib.h>
#include <QTcpSocket>
#include <QMap>
#include <QString>
#include <iostream>
#include "gamethread.h"

Server::Server(QObject *parent)
    : QTcpServer(parent)
{
}

void Server::incomingConnection(QTcpSocket ts)
{
    tcpSocket = new QTcpSocket();

    if (player == NULL)
    {
        //playerSocketDescriptor = socketDescriptor;
        player = tcpSocket;
    }
    else
    {
        GameThread *thread = new GameThread(player, tcpSocket, this);
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
        thread->start();

        player = NULL;
    }
}

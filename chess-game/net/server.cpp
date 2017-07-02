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

void Server::incomingConnection(qintptr socketDescriptor)
{
    tcpSocket = new QTcpSocket();
    tcpSocket->setSocketDescriptor(socketDescriptor);

    if (player == NULL)
    {
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

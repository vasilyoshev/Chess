#include "server.h"
#include "thread.h"
#include <stdlib.h>
#include <QTcpSocket>
#include <QMap>

Server::Server(QObject *parent)
    : QTcpServer(parent)
{
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    //Thread *thread = new Thread(socketDescriptor, this);
    //connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    //thread->start();

    QTcpSocket tcpSocket;
    tcpSocket.setSocketDescriptor(socketDescriptor);

    //QByteArray block;
    //QDataStream in(&block, QIODevice::ReadOnly);
    //in.setVersion(QDataStream::Qt_4_0);
    //in >> text;
    //tcpSocket.readAll();

    QDataStream in(tcpSocket);
    QString name;
    in >> name;
    players.insert(name, socketDescriptor);
}


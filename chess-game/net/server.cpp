#include "server.h"
#include "thread.h"
#include <stdlib.h>
#include <QTcpSocket>
#include <QMap>
#include <QString>
#include <iostream>

Server::Server(QObject *parent)
    : QTcpServer(parent)
{
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    tcpSocket = new QTcpSocket();
    tcpSocket->setSocketDescriptor(socketDescriptor);
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
}

void Server::readyRead()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::ReadOnly);
    out << tcpSocket->readAll();
    QString name(block);
    players.insert(name, tcpSocket);
}

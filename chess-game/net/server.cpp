#include "server.h"
#include "thread.h"
#include <stdlib.h>
#include <QTcpSocket>
#include <QMap>
#include <QString>

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
    QString name;
    //in.setDevice(tcpSocket);
    //in.setVersion(QDataStream::Qt_4_0);
    in.startTransaction();
    in >> name;
    in.commitTransaction();
    players.insert(name, &tcpSocket);
    QTextStream out(stdout, QIODevice::WriteOnly);
    out << players.contains("Vasko");

    //QByteArray block;
    //QDataStream in(&block, QIODevice::ReadOnly);
    //in.setVersion(QDataStream::Qt_4_0);
    //in >> text;
    //tcpSocket.readAll();
}


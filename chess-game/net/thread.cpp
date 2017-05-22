#include "thread.h"
#include "mainwindow.h"
#include "controller.h"
#include "server.h"

#include <QtNetwork>

Thread::Thread(int socketDescriptor, QObject *parent)
    : QThread(parent), socketDescriptor(socketDescriptor) /*text(fortune)*/
{
}

void Thread::run()
{

    QTcpSocket tcpSocket;
    if (!tcpSocket.setSocketDescriptor(socketDescriptor)) {
        emit error(tcpSocket.error());
        return;
    }
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    tcpSocket.write(block);






    tcpSocket.disconnectFromHost();
    tcpSocket.waitForDisconnected();
}

#include "server.h"
#include "thread.h"

#include <stdlib.h>

Server::Server(QObject *parent)
    : QTcpServer(parent)
{
    fortunes << tr("You've been leading a dog's life. Stay off the furniture.")
             << tr("You've got to think about tomorrow.")
             << tr("You will be surprised by a loud noise.")
             << tr("You will feel hungry again in another hour.")
             << tr("You might have mail.")
             << tr("You cannot kill time without injuring eternity.")
             << tr("Computers are not intelligent. They only think they are.");

    waiting = false;
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    //QString fortune = fortunes.at(qrand() % fortunes.size()); // TODO remove


    Thread *thread = new Thread(socketDescriptor, fortune, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();

}


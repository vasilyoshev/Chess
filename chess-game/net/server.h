#ifndef SERVER_H
#define SERVER_H

#include <QString>
#include <QTcpServer>
#include <QMap>
#include <QTcpSocket>

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server(QObject *parent = 0);

protected:
    void incomingConnection(qintptr socketDescriptor) override;
    QMap<QString, int> players;
};

#endif

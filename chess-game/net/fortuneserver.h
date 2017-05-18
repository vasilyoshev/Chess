#ifndef FORTUNESERVER_H
#define FORTUNESERVER_H

#include <QStringList>
#include <QTcpServer>

class FortuneServer : public QTcpServer
{
    Q_OBJECT

public:
    FortuneServer(QObject *parent = 0);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private:
    QStringList fortunes;
};

#endif

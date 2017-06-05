#ifndef FORTUNETHREAD_H
#define FORTUNETHREAD_H

#include <QThread>
#include <QTcpSocket>

class Thread : public QThread
{
    Q_OBJECT
public:
    Thread(int socketDescriptor, QObject *parent);
    void run() override;
    QString playerName;

signals:
    void error(QTcpSocket::SocketError socketError);

private:
    int socketDescriptor;
    void receiveName();
};

#endif

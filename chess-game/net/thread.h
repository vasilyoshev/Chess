#ifndef FORTUNETHREAD_H
#define FORTUNETHREAD_H

#include <QThread>
#include <QTcpSocket>

class Thread : public QThread
{
    Q_OBJECT

public:
    Thread(int socketDescriptor, const QString &fortune, QObject *parent);

    void run() override;

signals:
    void error(QTcpSocket::SocketError socketError);

private:
    int socketDescriptor;
    QString text;
    bool waiting;
};

#endif

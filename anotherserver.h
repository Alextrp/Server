#ifndef ANOTHERSERVER_H
#define ANOTHERSERVER_H

#include <QObject>
#include <QUdpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkDatagram>
#include <QDebug>

class AnotherServer : public QObject {
    Q_OBJECT

public:
    explicit AnotherServer(QObject *parent = nullptr);

    void requestTact(quint16 portTime);
    qint64 takt;


private slots:
    void processPendingDatagrams();

private:
    QUdpSocket *udpSocket;
};

#endif // ANOTHERSERVER_H

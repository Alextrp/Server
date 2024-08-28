#include "server.h"
#include "validation.h"
#include "anotherserver.h"

Server::Server()
{
    if(this->listen(QHostAddress::Any,2323))
    {
        qDebug() << "Server start";
    }
    else
    {
        qDebug() << "error";
    }
    nextBlockSize = 0;

    anotherServer = new AnotherServer(this);
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    Sockets.push_back(socket);
    qDebug() << "client connected" << socketDescriptor;

    anotherServer = new AnotherServer(this);

    // Создаем и настраиваем таймер
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() { anotherServer->requestTact(portTime); });
    timer->start(1000);
}

void Server::slotReadyRead() {
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);
    if (in.status() == QDataStream::Ok) {
        for (;;) {
            if (nextBlockSize == 0) {
                if (socket->bytesAvailable() < 2) {
                    break;
                }
                in >> nextBlockSize;
            }
            if (socket->bytesAvailable() < nextBlockSize) {
                break;
            }

            QString jsonString;
            in >> jsonString;
            nextBlockSize = 0;

            QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
            QJsonObject json = doc.object();

            // Используем текущий такт из AnotherServer
            qint64 tactNumber = anotherServer->takt;
            json["tact_number"] = tactNumber;

            qDebug() << "Received JSON:";
            qDebug() << "ID:" << json["id"].toInt();
            qDebug() << "Timestamp:" << json["timestamp"].toString();
            qDebug() << "Config:" << json["config"].toString();
            qDebug() << "Priority:" << json["priority"].toInt();
            qDebug() << "Min Count:" << json["min_count"].toInt();
            qDebug() << "Tact Number:" << tactNumber;

            SendToClient(QJsonDocument(json).toJson());
            break;
        }
    } else {
        qDebug() << "DataStream error";
    }
}


void Server::SendToClient(QString str)
{
    /*QJsonObject json;
    json["response"] = str;

    QJsonDocument doc(json);
    QString jsonString = doc.toJson(QJsonDocument::Compact);*/

    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out << quint16(0) << str;
    out.device()->seek(0);
    out << quint16(Data.size()-sizeof(quint16));

    //socket->write(Data);
    for(int i = 0; i < Sockets.size(); i++)
    {
        Sockets[i]->write(Data);
    }
}


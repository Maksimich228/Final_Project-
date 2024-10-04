#include "server.h"
#include <QTextStream>

Server::Server(QObject *parent) : QTcpServer(parent) {}

void Server::startServer() {
    if (this->listen(QHostAddress::Any, 1234)) {
        qDebug() << "Server started on port 1234";
    } else {
        qDebug() << "Failed to start the server!";
    }
}

void Server::onNewConnection() {
    QTcpSocket *clientSocket = this->nextPendingConnection();
    clients.push_back(clientSocket);
    connect(clientSocket, &QTcpSocket::disconnected, this, &Server::onClientDisconnected);
    connect(clientSocket, &QTcpSocket::readyRead, this, &Server::onReadyRead);
    qDebug() << "New client connected!";
}

void Server::onClientDisconnected() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    clients.erase(std::remove(clients.begin(), clients.end(), clientSocket), clients.end());
    clientSocket->deleteLater();
    qDebug() << "Client disconnected!";
}

void Server::onReadyRead() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    QTextStream in(clientSocket);
    QString message = in.readAll();

    qDebug() << "Received message:" << message;
    sendMessageToAllClients(message);
}

void Server::sendMessageToAllClients(const QString &message) {
    for (QTcpSocket *client : clients) {
        QTextStream out(client);
        out << message;
        client->flush();
    }
}

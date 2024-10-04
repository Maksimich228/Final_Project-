#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <vector>

class Server : public QTcpServer {
    Q_OBJECT

public:
    explicit Server(QObject *parent = nullptr);
    void startServer();
    void sendMessageToAllClients(const QString &message);

private slots:
    void onNewConnection();
    void onClientDisconnected();
    void onReadyRead();

private:
    std::vector<QTcpSocket*> clients;
};

#endif // SERVER_H


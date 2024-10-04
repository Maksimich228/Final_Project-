#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QTcpSocket>
#include <string>
#include <vector>

namespace Ui {
class MainWindow;
}

struct User {
    std::string username;
    bool isBanned;
};

struct Message {
    std::string sender;
    std::string content;
};

class Messenger {
public:
    Messenger();
    void addUser(const std::string& username);
    void addMessage(const std::string& sender, const std::string& content);
    void banUser(const std::string& username);

    std::vector<User> users;
    std::vector<Message> messages;
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_sendButton_clicked();
    void on_loginButton_clicked();
    void on_userListWidget_itemClicked(QListWidgetItem* item);
    void on_banButton_clicked();
    void onConnected();
    void onReadyRead();

private:
    void updateUserList();
    void updateMessageList();

    Ui::MainWindow *ui;
    Messenger messenger;
    std::string currentUser;
    QTcpSocket *socket;
};

#endif // MAINWINDOW_H



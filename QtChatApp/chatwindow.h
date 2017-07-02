#pragma once

#include "qtclient.h"
#include "qtserver.h"

#include <QDebug>
#include <QWidget>


namespace Ui {
class ChatWindow;
}

class ChatWindow : public QWidget {
    Q_OBJECT

public:
    explicit ChatWindow(QWidget* parent = 0);
    ~ChatWindow();

    void changeChatWindowTitle(bool isUserTypeServer);
    void showChatWindow();
    void startServer();
    void startClient(const QString& ipAdd);
    void closeEvent(QCloseEvent* event);

private:
    Ui::ChatWindow* m_chatWindowUi;
    QtServer* m_server;
    QtClient* m_client;
    QString m_userType;
    const QString m_serverStr;
    const QString m_clientStr;

signals:
     void signalSendMessage(const QString& qstrMessage);

public slots:
    void slotDisplayMessage(const QString& qstrMessage);
    void slotSendMessage();
};


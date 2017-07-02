#pragma once

#include <QAbstractSocket>
#include <QDebug>
#include <QObject>
#include <QTcpSocket>



class ChatWindow;

class QtClient : public QObject {
    Q_OBJECT
public:
    explicit QtClient(ChatWindow*);
    void startClient(const QString& ipAddress);
    ~QtClient();
signals:
     void signalReceivedMsg(const QString& qstrMessage);

public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void slotSendMessage(const QString& qstrMessage);

private:
    QTcpSocket* m_clientSocket;
    ChatWindow* m_chatWindow;
};

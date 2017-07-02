#pragma once

#include <QDebug>
#include <QObject>
#include <QTcpSocket>
#include <QThread>


class ChatWindow;

class QtThread : public QThread {
    Q_OBJECT
public:
    QtThread(qintptr, QObject*, ChatWindow*, QTcpSocket*);
    ~QtThread();
    void run();
    void writeToSocket(const QByteArray& message);
signals:
    void signalReceivedMsg(const QString& qstrMessage);

public slots:
    void readyRead();
    void disconnected();
    void bytesWritten(qint64 bytes);

private:
    ChatWindow* m_chatWindow;
    QTcpSocket* m_serverSocket;
    qintptr m_socketDiscriptor;
};

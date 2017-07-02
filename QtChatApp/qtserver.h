#pragma once

#include "qtthread.h"

#include <QDebug>
#include <QObject>
#include <QString>
#include <QTcpServer>


class ChatWindow;

class QtServer : public QTcpServer {
   Q_OBJECT
public:
   QtServer(ChatWindow* chatWindow = 0);
   void startServer();
   ~QtServer();

public slots:
   void slotSendMessage(const QString& qstrMessage);

protected:
   void incomingConnection(qintptr socketDescriptor);

private:
   ChatWindow* m_chatWindow;
   QtThread* m_thread;
   QTcpSocket* m_serverSocket;
};

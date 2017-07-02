#include "qtserver.h"


QtServer::QtServer(ChatWindow* chatWindow)
        : QTcpServer(Q_NULLPTR)
        , m_chatWindow(chatWindow)
        , m_thread(Q_NULLPTR)
        , m_serverSocket(Q_NULLPTR)
{

}

QtServer::~QtServer()
{

}

void QtServer::startServer()
{
    if (!this->listen(QHostAddress::Any, 1234))
        qDebug() << "Could not start server";
    else
        qDebug() << "Server started and listening ";
}

void QtServer::incomingConnection(qintptr socketDescriptor)
{
    m_serverSocket = new QTcpSocket(this);
    if (!m_serverSocket->setSocketDescriptor(socketDescriptor)) { // Setting the id
         qDebug() << "couldn't set the descriptor";
         return;
    }
    m_thread = new QtThread(socketDescriptor, this, m_chatWindow, m_serverSocket);
    connect(m_thread, SIGNAL(finished()), m_thread, SLOT(deleteLater()));
    connect(m_serverSocket, SIGNAL(readyRead()), m_thread, SLOT(readyRead()), Qt::DirectConnection);
    connect(m_serverSocket, SIGNAL(disconnected()), m_thread,SLOT(disconnected()));
    connect(m_serverSocket, SIGNAL(bytesWritten(qint64)), m_thread, SLOT(bytesWritten(qint64)));
    m_thread->start();
}

void QtServer::slotSendMessage(const QString& message)
{    
    QByteArray textMessage = message.toUtf8();
    m_thread->writeToSocket(message.toUtf8());
}



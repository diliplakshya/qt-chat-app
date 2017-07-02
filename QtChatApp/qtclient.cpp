#include "qtclient.h"

#include "chatwindow.h"

QtClient::QtClient(ChatWindow* chatWindow)
   : QObject(Q_NULLPTR)
   , m_clientSocket(new QTcpSocket(this))
   , m_chatWindow(chatWindow)
{

}

QtClient::~QtClient()
{
    delete m_clientSocket;
}

void QtClient::startClient(const QString& ipAddress)
{
    connect(m_clientSocket, SIGNAL(connected()), this, SLOT(connected()));
    connect(m_clientSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(m_clientSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(m_clientSocket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
    connect(this, SIGNAL(signalReceivedMsg(const QString&)), m_chatWindow, SLOT(slotDisplayMessage(const QString&)));
    m_clientSocket->connectToHost(ipAddress, 1234);
}

void QtClient::connected()
{
    qDebug() << "Server Connected!";
}

void QtClient::disconnected()
{
    qDebug() << "Server Disconnected!";
    m_clientSocket->deleteLater();
}

void QtClient::bytesWritten(qint64 bytes)
{
    qDebug() << "Client wrote: " << bytes;
}

void QtClient::readyRead()
{
    QByteArray data = m_clientSocket->readAll();
    qDebug() << "Received Data : " << data;
    emit signalReceivedMsg("Server : " + QString(data));
}

//send message to server
void QtClient::slotSendMessage(const QString& qstrMessage)
{    
    if (m_clientSocket->state() == QAbstractSocket::ConnectedState)
        m_clientSocket->write(qstrMessage.toUtf8());
}



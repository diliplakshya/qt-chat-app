#include "qtthread.h"

#include "chatwindow.h"

QtThread::QtThread(qintptr ID, QObject* parent, ChatWindow* chatWindow, QTcpSocket* serverSocket)
         : QThread(parent)
         , m_chatWindow(chatWindow)
         , m_serverSocket(serverSocket)
         , m_socketDiscriptor(0)
{
    this->m_socketDiscriptor = ID;
}

QtThread::~QtThread()
{

}

void QtThread::run()
{
    qDebug() << " Thread started";
    qDebug() << m_socketDiscriptor << " Client connected";
    connect(this,SIGNAL(signalReceivedMsg(const QString&)), m_chatWindow,SLOT(slotDisplayMessage(const QString&)));
    exec();
}

void QtThread::writeToSocket(const QByteArray& message)
{
    if (m_serverSocket->state() == QAbstractSocket::ConnectedState)
        m_serverSocket->write(message);
}

void QtThread::readyRead()
{
    QByteArray data = m_serverSocket->readAll();
    qDebug() << m_socketDiscriptor << "Data :" << data;
    emit signalReceivedMsg("Client : "+QString(data));
}

void QtThread::disconnected()
{
    qDebug() << m_socketDiscriptor << " Disconnected";
    m_serverSocket->deleteLater();
    exit(0);
}

void QtThread::bytesWritten(qint64 bytes)
{
    qDebug() << "Server wrote: " << bytes;
}

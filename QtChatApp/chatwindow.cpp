#include "chatwindow.h"

#include "ui_chatwindow.h"


ChatWindow::ChatWindow(QWidget* parent)
    : QWidget(parent)
    , m_chatWindowUi(new Ui::ChatWindow)
    , m_server(Q_NULLPTR)
    , m_client(Q_NULLPTR)
    , m_userType(QString::null)
    , m_serverStr("Server")
    , m_clientStr("Client")
{
    m_chatWindowUi->setupUi(this);
    m_chatWindowUi->plainTextEditMessageDisplay->setReadOnly(true);
    m_chatWindowUi->plainTextEditMessageDisplay->setStyleSheet("QPlainTextEdit{color: #ffff00; background-color: #303030;"
                                                   " selection-background-color: #606060; selection-color: #ffffff;}");
    connect(m_chatWindowUi->pushButtonMessageSend, SIGNAL(clicked()), this, SLOT(slotSendMessage()));
}

ChatWindow::~ChatWindow()
{
    delete m_chatWindowUi;
}

void ChatWindow::changeChatWindowTitle(bool isUserTypeServer)
{
   if (isUserTypeServer)
      this->m_userType = m_serverStr;
   else
       this->m_userType = m_clientStr;
   m_chatWindowUi->labelUserType->setText(this->m_userType);
}

void ChatWindow::showChatWindow()
{
    this->show();
}

void ChatWindow::startServer()
{
    m_server = new QtServer(this);
    m_server->startServer();
    connect(this, SIGNAL(signalSendMessage(const QString&)), m_server, SLOT(slotSendMessage(const QString&)));
}

void ChatWindow::startClient(const QString& ipAdd)
{
    m_client = new QtClient(this);
    m_client->startClient(ipAdd);
    connect(this, SIGNAL(signalSendMessage(const QString&)), m_client, SLOT(slotSendMessage(const QString&)));
}

void ChatWindow::slotDisplayMessage(const QString& qstrMessage)
{
    m_chatWindowUi->plainTextEditMessageDisplay->appendPlainText(qstrMessage);
}

void ChatWindow::slotSendMessage()
{
    // Signal the server/client to send the message
    emit signalSendMessage( m_chatWindowUi->plainTextEdit->toPlainText());
    slotDisplayMessage(m_userType+" : "+m_chatWindowUi->plainTextEdit->toPlainText());
    m_chatWindowUi->plainTextEdit->clear();
}

void ChatWindow::closeEvent(QCloseEvent* event)
{
    if (m_server)
        m_server->close();
}


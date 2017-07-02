#include "clientconnectwindow.h"
#include "chatwindow.h"

#include "ui_clientconnectwindow.h"



ClientConnectWindow::ClientConnectWindow(QWidget* parent)
    : QWidget(parent)
    , m_clientConnectedWindowUi(new Ui::ClientConnectWindow)
    , m_chatWindow(Q_NULLPTR)
{
    m_clientConnectedWindowUi->setupUi(this);

    m_clientConnectedWindowUi->pushButtonConnect->setEnabled(false); // Disable Go push button.

    connect(m_clientConnectedWindowUi->lineEditServerIP, &QLineEdit::textChanged, this, &ClientConnectWindow::slotServerIPEntered);
    connect(m_clientConnectedWindowUi->pushButtonConnect, &QAbstractButton::clicked, this, &ClientConnectWindow::slotButtonConnectClicked);
}

ClientConnectWindow::~ClientConnectWindow()
{
    delete m_clientConnectedWindowUi;
}

void ClientConnectWindow::slotButtonConnectClicked() // Hide client connect window.
{
    this->hide();
    m_chatWindow = new ChatWindow();
    m_chatWindow->startClient(m_clientConnectedWindowUi->lineEditServerIP->text());
    m_chatWindow->changeChatWindowTitle(false);
    m_chatWindow->showChatWindow();
}

void ClientConnectWindow::slotServerIPEntered() // Server ip has some text.
{
    if (!m_clientConnectedWindowUi->lineEditServerIP->text().isEmpty())
        m_clientConnectedWindowUi->pushButtonConnect->setEnabled(true);
}

void ClientConnectWindow::showClientWindow() //Show client window when user type is Client.
{
    this->show();
}

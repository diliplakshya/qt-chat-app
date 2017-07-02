#include "mainwindow.h"

#include "chatwindow.h"
#include "clientconnectwindow.h"

#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent)
    , m_MainWindowUi(new Ui::MainWindow)
    , m_chatWindow(Q_NULLPTR)
    , m_clientConnectWindow(Q_NULLPTR)
{
    m_MainWindowUi->setupUi(this);

    m_MainWindowUi->pushButtonGo->setEnabled(false); // Disable Go push button

    m_clientConnectWindow = new ClientConnectWindow();
    m_chatWindow = new ChatWindow();

    connect(m_MainWindowUi->radioButtonSelectServer, SIGNAL(clicked()), this, SLOT(slotUserTypeSelected()));
    connect(m_MainWindowUi->radioButtonSelectClient, SIGNAL(clicked()), this, SLOT(slotUserTypeSelected()));
    connect(m_MainWindowUi->pushButtonGo, SIGNAL(clicked()), this, SLOT(slotButtonGoClicked()));

}

MainWindow::~MainWindow()
{
    delete m_MainWindowUi;
}

void MainWindow::slotUserTypeSelected()
{
    if (!m_MainWindowUi->pushButtonGo->isEnabled())
        m_MainWindowUi->pushButtonGo->setEnabled(true);
}

void MainWindow::slotButtonGoClicked()
{
    this->hide();
    if (m_MainWindowUi->radioButtonSelectServer->isChecked()) {
        m_chatWindow->changeChatWindowTitle(m_MainWindowUi->radioButtonSelectServer->isChecked());
        m_chatWindow->showChatWindow();
        m_chatWindow->startServer();
    } else
        m_clientConnectWindow->showClientWindow();
}



#pragma once

#include "qtclient.h"

#include <QWidget>

namespace Ui {
class ClientConnectWindow;
}

class ChatWindow;


class ClientConnectWindow : public QWidget {
    Q_OBJECT

public:
    explicit ClientConnectWindow(QWidget* parent = 0);
    ~ClientConnectWindow();
    void showClientWindow();

private:
    Ui::ClientConnectWindow* m_clientConnectedWindowUi;
    ChatWindow* m_chatWindow;

public slots:
    void slotButtonConnectClicked();
    void slotServerIPEntered();
};


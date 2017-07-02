#pragma once

#include <QWidget>

namespace Ui {
class MainWindow;
}

class ChatWindow;
class ClientConnectWindow;

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow* m_MainWindowUi;
    ChatWindow* m_chatWindow;
    ClientConnectWindow* m_clientConnectWindow;

signals:
    void signalServerSelected();
    void signalClientSelected();

public slots:
    void slotButtonGoClicked();
    void slotUserTypeSelected();
};

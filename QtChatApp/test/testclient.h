#ifndef TESTCLIENT_H
#define TESTCLIENT_H

#include <QObject>

class TestClient : public QObject
{
    Q_OBJECT
public:
    explicit TestClient(QObject *parent = 0);

signals:

public slots:
};

#endif // TESTCLIENT_H
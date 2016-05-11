#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = 0);
    QTcpSocket *client;

signals:
    void diplayMessage(QString message);
    void displayValue(int deviceid, QString transfertype, QString devicevalue);

public slots:
    void readMessage();
    void sendMessage(int deviceid, int devicetype, QString devicevalue);
    void newConnect();
};

#endif // TCPCLIENT_H

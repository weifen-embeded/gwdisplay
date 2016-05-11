#include "tcpclient.h"

TcpClient::TcpClient(QObject *parent) : QObject(parent)
{
    client = new QTcpSocket(this);
    connect(client,SIGNAL(readyRead()),this,SLOT(readMessage()));
    this->newConnect();

}

void TcpClient::newConnect()
{
    client->abort();
    //client->connectToHost("192.168.1.133",51001);
    client->connectToHost("127.0.0.1",51001);
    this->client->write("{\"cmd\":\"request_push\"}\n");
}

void TcpClient::readMessage()
{
    int dvid;
    QString tstp;
    QString dvvl;
    while(client->canReadLine())
    {
        QByteArray  message = client->readLine();
        QString msg_str = message;
        emit this->diplayMessage(msg_str);
        qDebug()<<msg_str;

        QJsonParseError json_error;
        QJsonDocument parse_document = QJsonDocument::fromJson(message, &json_error);
        if(json_error.error == QJsonParseError::NoError)
        {
            QJsonObject obj = parse_document.object();
            if(obj.contains("device_id"))
            {
                QJsonValue device_id = obj.take("device_id");
                if(device_id.isDouble())
                {
                    dvid = device_id.toInt();
                }
            }

            if(obj.contains("transfer_type"))
            {
                QJsonValue transfer_type = obj.take("transfer_type");
                if(transfer_type.isString())
                {
                    tstp = transfer_type.toString();
                }
            }

            if(obj.contains("device_value"))
            {
                QJsonValue device_value = obj.take("device_value");
                if(device_value.isString())
                {
                    dvvl = device_value.toString();
                }
            }
        }
        emit this->displayValue(dvid,tstp,dvvl);
    }
}

void TcpClient::sendMessage(int deviceid, int devicetype,  QString devicevalue)
{
    QJsonObject object;
    object.insert("cmd","set_switch");
    QJsonObject object_args;
    object_args.insert("device_id",deviceid);
    object_args.insert("device_type",devicetype);
    object_args.insert("device_value", devicevalue);
    object.insert("args",object_args);

    QJsonDocument document;
    document.setObject(object);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);

    /*向服务器发送字符串*/
    this->client->write(byte_array+"\n");
}

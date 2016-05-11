#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "tcpclient.h"
#include <QMovie>
#include <QNetworkInterface>
#include <QTimer>
#include <QProcess>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    TcpClient *tcpclient;
    QMovie *movie;
    QTimer *timer;
    QString getLocalIP(); //获取本地IP地址
    bool textBrowser_flag;
    bool led_flag;
    bool fan_flag;
    bool led_show_flag;
    int num_flag[13];

signals:
    void sendMessage(int deviceid, int devicetype, QString devicevalue);
    void newConnect();

private slots:
    void on_pushButton_sensor_clicked();

    void on_pushButton_debug_clicked();

    void on_pushButton_left_clicked();

    void on_pushButton_right_clicked();

    void diplayMessage(QString msg);
    void displayValue(int deviceid, QString transfertype, QString devicevalue);

    void on_pushButton_led_clicked();

    void on_pushButton_fan_clicked();

    void on_pushButton_connect_clicked();

    void on_pushButton_getip_clicked();

    void on_pushButton_suspend_clicked();

    void on_pushButton_clear_clicked();
    void qtimeSlot();

    void on_pushButton_update_clicked();

    void on_pushButton_online_clicked();

    void on_pushButton_offline_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H

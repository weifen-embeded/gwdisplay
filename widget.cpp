#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    tcpclient = new TcpClient(this);
    movie = new QMovie(":/new/prefix1/image/fan_m40x40.gif");
    timer = new QTimer(this);
    ui->fan_vl->setMovie(movie);
    connect(tcpclient,SIGNAL(diplayMessage(QString)),this,SLOT(diplayMessage(QString)));
    connect(tcpclient,SIGNAL(displayValue(int,QString,QString)),this,SLOT(displayValue(int,QString,QString)));
    connect(this,SIGNAL(sendMessage(int,int,QString)),tcpclient,SLOT(sendMessage(int,int,QString)));
    connect(this,SIGNAL(newConnect()),tcpclient,SLOT(newConnect()));
    connect(timer, SIGNAL(timeout()), this, SLOT(qtimeSlot()));
    timer->start(20000);
    ui->label_ip->setText(getLocalIP());
    /*全局变量初始化*/
    textBrowser_flag = true;
    led_flag = true;
    fan_flag = true;
    led_show_flag = true;
    /*按键事件效果*/
    ui->pushButton_sensor->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/image/sensor.png);}"
    "QPushButton:hover{border-image: url(:/new/prefix1/image/sensor.png);}"
    "QPushButton:pressed{border-image: url(:/new/prefix1/image/sensor_OutLight.png);}");
    ui->pushButton_debug->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/image/debug.png);}"
    "QPushButton:hover{border-image: url(:/new/prefix1/image/debug.png);}"
    "QPushButton:pressed{border-image: url(:/new/prefix1/image/debug_OutLight.png);}");
    ui->pushButton_update->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/image/update.png);}"
    "QPushButton:hover{border-image: url(:/new/prefix1/image/update.png);}"
    "QPushButton:pressed{border-image: url(:/new/prefix1/image/update_OutLight.png);}");
    ui->pushButton_left->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/image/left.png);}"
    "QPushButton:hover{border-image: url(:/new/prefix1/image/left.png);}"
    "QPushButton:pressed{border-image: url(:/new/prefix1/image/left_OutLight.png);}");
    ui->pushButton_right->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/image/right.png);}"
    "QPushButton:hover{border-image: url(:/new/prefix1/image/right.png);}"
    "QPushButton:pressed{border-image: url(:/new/prefix1/image/right_OutLight.png);}");
    ui->pushButton_connect->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/image/push_up.png);}"
    "QPushButton:hover{border-image: url(:/new/prefix1/image/push_up.png);}"
    "QPushButton:pressed{border-image: url(:/new/prefix1/image/push_down.png);}"
    "QPushButton{color: rgb(255, 255, 255);}");
    ui->pushButton_getip->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/image/push_up.png);}"
    "QPushButton:hover{border-image: url(:/new/prefix1/image/push_up.png);}"
    "QPushButton:pressed{border-image: url(:/new/prefix1/image/push_down.png);}"
    "QPushButton{color: rgb(255, 255, 255);}");
    ui->pushButton_suspend->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/image/push_up.png);}"
    "QPushButton:hover{border-image: url(:/new/prefix1/image/push_up.png);}"
    "QPushButton:pressed{border-image: url(:/new/prefix1/image/push_down.png);}"
    "QPushButton{color: rgb(255, 255, 255);}");
    ui->pushButton_clear->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/image/push_up.png);}"
    "QPushButton:hover{border-image: url(:/new/prefix1/image/push_up.png);}"
    "QPushButton:pressed{border-image: url(:/new/prefix1/image/push_down.png);}"
    "QPushButton{color: rgb(255, 255, 255);}");

    ui->label_31->hide();
    ui->led_id->hide();
    ui->led_tp->hide();
    ui->led_vl->hide();
    ui->pushButton_led->hide();
    ui->widget2->setGeometry(410,0,375,311);

    int i;
    for(i = 0; i < 13; i ++)
        num_flag[i]=0;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::diplayMessage(QString message)
{
    if(textBrowser_flag == true)
        ui->textBrowser->append(message);
    else
    {}
}

//获取本地IP地址
QString Widget::getLocalIP()
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list)
    {
        //使用IPv4地址
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
        {
            if (address.toString().contains("127.0."))
                continue;
            else
                return address.toString();
        }
    }
    return 0;
 }

void Widget::displayValue(int deviceid, QString transfertype, QString devicevalue)
{
    switch (deviceid) {
    case 0x01:
        num_flag[0]++;
        ui->tem_id->setText("1");
        ui->tem_vl->setText(devicevalue);
        ui->tem_tp->setText(transfertype);
        break;
    case 0x02:
        num_flag[1]++;
        ui->hum_id->setText("2");
        ui->hum_vl->setText(devicevalue);
        ui->hum_tp->setText(transfertype);
        break;
    case 0x03:
        num_flag[2]++;
        ui->lig_id->setText("3");
        ui->lig_vl->setText(devicevalue);
        ui->lig_tp->setText(transfertype);
        break;
    case 0x04:
        num_flag[3]++;
        ui->six_id->setText("4");
        ui->six_vl_ax->setText(devicevalue.split(",").at(0));
        ui->six_vl_ay->setText(devicevalue.split(",").at(1));
        ui->six_vl_az->setText(devicevalue.split(",").at(2));
        ui->six_vl_gx->setText(devicevalue.split(",").at(3));
        ui->six_vl_gy->setText(devicevalue.split(",").at(4));
        ui->six_vl_gz->setText(devicevalue.split(",").at(5));
        ui->six_tp->setText(transfertype);
        break;
    case 0x07:
        num_flag[4]++;
        ui->gas_id->setText("7");
        ui->gas_vl->setText(devicevalue);
        ui->gas_tp->setText(transfertype);
        break;
    case 0x08:
        num_flag[5]++;
        ui->smo_id->setText("8");
        ui->smo_vl->setText(devicevalue);
        ui->smo_tp->setText(transfertype);
        break;
    case 0x0A:
        num_flag[6]++;
        ui->mag_id->setText("10");
        ui->mag_vl_x->setText(devicevalue.split(",").at(0));
        ui->mag_vl_y->setText(devicevalue.split(",").at(1));
        ui->mag_vl_z->setText(devicevalue.split(",").at(2));
        ui->mag_tp->setText(transfertype);
        break;
    case 0x65:
        num_flag[7]++;
        if(led_show_flag == true)
        {
            led_show_flag = false;
            ui->label_31->show();
            ui->led_id->show();
            ui->led_tp->show();
            ui->led_vl->show();
            ui->pushButton_led->show();
            ui->widget2->setGeometry(410,0,361,351);
        }
        else {}

        ui->led_id->setText("101");
        if(devicevalue == "false")
            ui->led_vl->setStyleSheet("QLabel{border-image: url(:/new/prefix1/image/led_off40x40.png);}");
        else if(devicevalue == "true")
            ui->led_vl->setStyleSheet("QLabel{border-image: url(:/new/prefix1/image/led_on40x40.png);}");
        ui->led_tp->setText(transfertype);
        break;
    case 0x66:
        num_flag[8]++;
        ui->fan_id->setText("102");
        if(devicevalue == "false")
            this->movie->stop();
        else if(devicevalue == "true")
            this->movie->start();
        ui->fan_tp->setText(transfertype);
        break;
    case 0x97:
        num_flag[9]++;
        ui->inf_id->setText("151");
        if(devicevalue == "false")
            ui->inf_vl->setStyleSheet("QLabel{border-image: url(:/new/prefix1/image/hong_hb.png);}");
        else if(devicevalue == "true")
            ui->inf_vl->setStyleSheet("QLabel{border-image: url(:/new/prefix1/image/hong_cs.png);}");
        ui->inf_tp->setText(transfertype);
        break;
    case 0x99:
        num_flag[10]++;
        ui->tou_id->setText("153");
        if(devicevalue == "false")
            ui->tou_vl->setStyleSheet("QLabel{border-image: url(:/new/prefix1/image/touch_off.png);}");
        else if(devicevalue == "true")
            ui->tou_vl->setStyleSheet("QLabel{border-image: url(:/new/prefix1/image/touch_on.png);}");
        ui->tou_tp->setText(transfertype);
        break;
    case 0x9A:
        num_flag[11]++;
        ui->voi_id->setText("154");
        if(devicevalue == "false")
            ui->voi_vl->setStyleSheet("QLabel{border-image: url(:/new/prefix1/image/voice_off.png);}");
        else if(devicevalue == "true")
            ui->voi_vl->setStyleSheet("QLabel{border-image: url(:/new/prefix1/image/voice_on.png);}");
        ui->voi_tp->setText(transfertype);
        break;
    case 0x9C:
        num_flag[12]++;
        ui->fir_id->setText("156");
        if(devicevalue == "false")
            ui->fir_vl->setStyleSheet("QLabel{border-image: url(:/new/prefix1/image/fire_n.png);}");
        else if(devicevalue == "true")
            ui->fir_vl->setStyleSheet("QLabel{border-image: url(:/new/prefix1/image/fire_y.png);}");
        ui->fir_tp->setText(transfertype);
        break;
    default:
        break;
    }
}

void Widget::on_pushButton_sensor_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Widget::on_pushButton_debug_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Widget::on_pushButton_left_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void Widget::on_pushButton_right_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void Widget::on_pushButton_led_clicked()
{
    if(led_flag==true)
    {
        led_flag=false;
        emit this->sendMessage(0x65,0x18,"true");
        ui->pushButton_led->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/image/off.png);}");
    }
    else if(led_flag==false)
    {
        led_flag=true;
        emit this->sendMessage(0x65,0x18,"false");
        ui->pushButton_led->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/image/on.png);}");
    }
}

void Widget::on_pushButton_fan_clicked()
{
    if(fan_flag==true)
    {
        fan_flag=false;
        emit this->sendMessage(0x66,0x18,"true");
        ui->pushButton_fan->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/image/off.png);}");
    }
    else if(fan_flag==false)
    {
        fan_flag=true;
        emit this->sendMessage(0x66,0x18,"false");
        ui->pushButton_fan->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/image/on.png);}");
    }
}

void Widget::on_pushButton_connect_clicked()
{
    emit this->newConnect();
}

void Widget::on_pushButton_getip_clicked()
{
    ui->label_ip->setText(getLocalIP());
}

void Widget::on_pushButton_suspend_clicked()
{
    if(textBrowser_flag==true)
    {
        textBrowser_flag=false;
        ui->pushButton_suspend->setText("开始");
    }
   else if(textBrowser_flag==false)
    {
        textBrowser_flag=true;
        ui->pushButton_suspend->setText("暂停");
    }
}

void Widget::on_pushButton_clear_clicked()
{
    ui->textBrowser->clear();
}

void Widget::qtimeSlot()
{
    if(textBrowser_flag == true)
        ui->textBrowser->clear();
    else {}

    if(num_flag[0] == 0)
    {
        ui->tem_id->setText("0");
        ui->tem_vl->setText("0");
        ui->tem_tp->setText("");
    }
    if(num_flag[1] == 0)
    {
        ui->hum_id->setText("0");
        ui->hum_vl->setText("0");
        ui->hum_tp->setText("");
    }
    if(num_flag[2] == 0)
    {
        ui->lig_id->setText("0");
        ui->lig_vl->setText("0");
        ui->lig_tp->setText("");
    }
    if(num_flag[3] == 0)
    {
        ui->six_id->setText("0");
        ui->six_vl_ax->setText("0");
        ui->six_vl_ay->setText("0");
        ui->six_vl_az->setText("0");
        ui->six_vl_gx->setText("0");
        ui->six_vl_gy->setText("0");
        ui->six_vl_gz->setText("0");
        ui->six_tp->setText("");
    }
    if(num_flag[4] == 0)
    {
        ui->gas_id->setText("0");
        ui->gas_vl->setText("0");
        ui->gas_tp->setText("");
    }
    if(num_flag[5] == 0)
    {
        ui->smo_id->setText("0");
        ui->smo_vl->setText("0");
        ui->smo_tp->setText("");
    }
    if(num_flag[6] == 0)
    {
        ui->mag_id->setText("0");
        ui->mag_vl_x->setText("0");
        ui->mag_vl_y->setText("0");
        ui->mag_vl_z->setText("0");
        ui->mag_tp->setText("");
    }
    if(num_flag[7] == 0)
    {
        ui->led_id->setText("0");
        ui->led_vl->setStyleSheet("QLabel{border-image: url(:/new/prefix1/image/led_off40x40.png);}");
        ui->led_tp->setText("");
    }
    if(num_flag[8] == 0)
    {
        ui->fan_id->setText("0");
        this->movie->stop();
        ui->fan_tp->setText("");
    }
    if(num_flag[9] == 0)
    {
        ui->inf_id->setText("0");
        ui->inf_vl->setStyleSheet("QLabel{border-image: url(:/new/prefix1/image/hong_hb.png);}");
        ui->inf_tp->setText("");
    }
    if(num_flag[10] == 0)
    {
        ui->tou_id->setText("0");
        ui->tou_vl->setStyleSheet("QLabel{border-image: url(:/new/prefix1/image/touch_off.png);}");
        ui->tou_tp->setText("");
    }
    if(num_flag[11] == 0)
    {
        ui->voi_id->setText("0");
        ui->voi_vl->setStyleSheet("QLabel{border-image: url(:/new/prefix1/image/voice_off.png);}");
        ui->voi_tp->setText("");
    }
    if(num_flag[12] == 0)
    {
        ui->fir_id->setText("0");
        ui->fir_vl->setStyleSheet("QLabel{border-image: url(:/new/prefix1/image/fire_n.png);}");
        ui->fir_tp->setText("");
    }
    int i;
    for(i = 0; i < 13; i ++)
        num_flag[i]=0;
}

void Widget::on_pushButton_update_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void Widget::on_pushButton_online_clicked()
{
    ui->label_text->setText("正在升级程序，升级完成会重启，请稍候 . . .");
    if(ui->comboBox_online->currentIndex() == 0)
        QProcess::execute("/root/on_gwdisplay.sh");
    else if(ui->comboBox_online->currentIndex() == 1)
        QProcess::execute("/root/on_gwdata-server.sh");
    else
    {}  
}

void Widget::on_pushButton_offline_clicked()
{
    ui->label_text->setText("正在升级程序，升级完成会重启，请稍候 . . .");
    if(ui->comboBox_offline->currentIndex() == 0)
        QProcess::execute("/root/off_gwdisplay.sh");
    else if(ui->comboBox_offline->currentIndex() == 1)
        QProcess::execute("/root/off_gwdata-server.sh");
    else
    {} 
}

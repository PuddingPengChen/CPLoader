#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    progress = 0;
    down = true;
    download = new QProcess();
    mySerialport = new QSerialPort();

    bConnect = false;

    download->setProcessChannelMode(QProcess::ForwardedChannels);
     connect(download,SIGNAL(readyReadStandardError()),this,SLOT(DownloadProgress()));
    connect(this,SIGNAL(Sig_WrittenFinisf()),this,SLOT(Slot_WrittenFinish()));
    //init serial and show it in the UI combo
    this->setWindowTitle(tr("mDraw-XLoader"));
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if (serial.open(QIODevice::ReadWrite))
        {
            qDebug()<<info.portName()<<info.description()<<info.manufacturer();
            comList.append(info.portName());
            serial.close();
        }
    }
    ui->portCombo->addItems(comList);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnFile_clicked()
{
    filename = QFileDialog::getOpenFileName(this,tr("打开文件"),".",tr("hex (*.hex)"));
    down = true;
}

void Widget::on_btnLoad_clicked()
{
    QStringList po;

    if(QFile("./1.jpg").exists())
    {
        QString arg = tr("-Uflash:w:%1:i").arg(filename);
        QString comName = "-P"+ui->portCombo->currentText();
        //UNO para
        //po<<"-C./avrdude.conf"<<"-v"<<"-v"<<"-v"<<"-v"<<"-patmega328p"<<"-carduino"<<comName<<"-b115200"<<"-D"<<arg;
        po<<"-C./avrdude.conf"<<"-v"<<"-v"<<"-v"<<"-v"<<"-patmega2560"<<"-cwiring"<<comName<<"-b115200"<<"-D"<<arg;
        download->start("./avrdude.exe",po);
        qDebug()<<po;
        download->waitForFinished();
        QMessageBox::information(this,tr("Note"),tr("Written finish!"));
    }

}


void Widget::DownloadProgress()
{

}
void Widget::Slot_WrittenFinish()
{
    QMessageBox::information(this,tr("Note"),tr("Written finish!"));
}

//connect btn
void Widget::on_btnConnect_clicked()
{
    comList.clear();
    ui->portCombo->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if (serial.open(QIODevice::ReadWrite))
        {
            qDebug()<<info.portName()<<info.description()<<info.manufacturer();
            comList.append(info.portName());
            serial.close();
        }
    }
    ui->portCombo->addItems(comList);
}

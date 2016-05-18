#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <QProcess>
#include <QSerialPort>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <httpwindow.h>


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_btnFile_clicked();

    void on_btnLoad_clicked();
    void DownloadProgress();
    void Slot_WrittenFinish();
    void on_btnConnect_clicked();
    void handleNetworkData(QNetworkReply*);

private:
    Ui::Widget *ui;
    QString filename;
    QProcess* download;

    int progress;
    bool down;

    //serial port
    QSerialPort *mySerialport;
    QStringList comList;
    bool bConnect;
signals:
    void Sig_WrittenFinisf();
};

#endif // WIDGET_H

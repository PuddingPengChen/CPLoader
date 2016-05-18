#include "widget.h"
#include <QApplication>
#include "httpwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    HttpWindow m;
    m.downloadFile();
    w.show();

    return a.exec();
}

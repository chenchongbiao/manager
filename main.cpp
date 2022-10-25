#include "mainwindow.h"
#include <DApplication>
#include <DWidgetUtil>

int main(int argc, char *argv[])
{
    DApplication a(argc, argv);
    MainWindow w;
    w.show();
    Dtk::Widget::moveToCenter(&w);
    return a.exec();
}

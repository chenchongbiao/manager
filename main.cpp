#include "widget.h"
#include <DApplication>
#include <DWidgetUtil>

int main(int argc, char *argv[])
{
    DApplication a(argc, argv);
    Widget w;
    w.show();
    Dtk::Widget::moveToCenter(&w);
    return a.exec();
}

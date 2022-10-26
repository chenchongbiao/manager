#include <DApplication>
#include <DWidgetUtil>
#include <DApplicationSettings>

#include "widget.h"

int main(int argc, char *argv[])
{
    DApplication a(argc, argv);
    a.loadTranslator();  // 载入翻译

//    DApplicationSettings settings;  // 保存窗口主题设置
    Widget w;
    w.show();
    Dtk::Widget::moveToCenter(&w);
    return a.exec();
}

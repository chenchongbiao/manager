#include <DApplication>
#include <DWidgetUtil>
#include <DApplicationSettings>

#include "widget.h"

int main(int argc, char *argv[])
{
    DApplication a(argc, argv);
    a.setOrganizationName("开发环境管理工具");
    a.setApplicationName("dev-manager");
    a.setApplicationVersion("1.0");
//    a.setProductIcon(QIcon(":/images/logo.svg"));
    a.setProductName("Dev-Manager");
    a.setApplicationDescription("这是一个集成环境软件，将开发环境做整合管理");

    a.loadTranslator();  // 载入翻译
    a.setApplicationDisplayName(QCoreApplication::translate("Main", ""));
    // 保存程序的窗口主题设置
    DApplicationSettings as;
    Q_UNUSED(as)

    Widget w;
    w.show();
    Dtk::Widget::moveToCenter(&w);
    return a.exec();
}

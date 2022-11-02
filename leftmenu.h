#ifndef LEFTMENU_H
#define LEFTMENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class LeftMenu : public QWidget
{
public:
    LeftMenu(QWidget *parent);
    void initUI(QWidget *parent);
    void checkMenu(QPushButton *btn,bool isCheck);

private:
    QWidget *leftMenuWidget;
    QList<QPushButton *> leftMenuList;  // 左侧菜单列表
    QPushButton *menuHome;              // 首页
    QPushButton *menuDocker;            // Docker
    QPushButton *menuFtp;               // FTP
    QPushButton *menuSql;               // 数据库
    QPushButton *menuProgram;           // 编程环境
    QPushButton *menuSoftware;          // 软件安装
    QPushButton *menuSetting;           // 设置
    QVBoxLayout *leftMenuWidgetLayout;  // 垂直布局
};

#endif // LEFTMENU_H

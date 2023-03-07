#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <DBlurEffectWidget>
#include <DTitlebar>
#include <QPushButton>

#include "PageHome/systeminfo.h"
#include "PageDocker/dockerpage.h"
#include "PageHome/leftmenu.h"
#include "PageHome/homepagestatus.h"
#include "PageFtp/ftppage.h"
#include "PageDatabase/dbpage.h"

DWIDGET_USE_NAMESPACE

namespace Ui {
class Widget;
}

class Widget : public DBlurEffectWidget // 继承自DTK的模糊窗口控件
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    DTitlebar *getTitlebar();

private:
    void initUI();                   // 初始化界面
    void reDrawUI();                 // 重新构造UI
    void chooseLeftMenu(int index);  // 左侧菜单切换

private:
    Ui::Widget *ui;
    DTitlebar *titlebar;             // 标题工具
    QPushButton *leftMenuList;       // 左侧菜单数组
    int nowMenu = 0;                 // 定位当前菜单
    SystemInfo *sytemInfo;           // 系统消息
    HomePageStatus *homePageStatus;  // 状态栏
    LeftMenu *leftMenu;              // 左侧菜单
    DockerPage *dockerPage;          // Docker管理
    FtpPage *ftpPage;                // Ftp管理
    DBPage *dbPage;                  // 数据库管理
};

#endif // WIDGET_H

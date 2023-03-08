#ifndef DBPAGE_H
#define DBPAGE_H

#include <QWidget>
#include <dboxwidget.h>
#include <DFrame>
#include <DPushButton>
#include <QVBoxLayout>
#include <QStackedWidget>

#include "common/multiselectlist.h"

DWIDGET_USE_NAMESPACE

class DBPage : public QWidget
{
    Q_OBJECT
public:
    explicit DBPage(QWidget *parent = nullptr);

private:
    void initUI();
    void chooseMenu(int index);         // 菜单切换
    void onMenuCheck(DPushButton *curBtn);  // 当菜单按钮被选中

private:
    QVBoxLayout *mainLayout;
    MultiSelectList *mysql;
    MultiSelectList *mongodb;
    QStackedWidget *stackedWidget;  // 存放多页面
    DHBoxWidget *subMenu;  // 顶部的菜单的容器
    QList<DPushButton *> topMenuList;  // 顶部菜单列表
    int nowMenu;  // 当前菜单
};

#endif // DBPAGE_H

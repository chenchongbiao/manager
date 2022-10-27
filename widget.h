#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <DBlurEffectWidget>
#include <DTitlebar>
#include <QPushButton>

#define LEFT_MENU_NUM 7

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
    void initUI();  // 初始化界面
    void reDrawUI();  // 重新构造UI
    void chooseLeftMenu(int index);  // 左侧菜单切换

private:
    Ui::Widget *ui;
    DTitlebar *titlebar;  // 标题工具
    QPushButton *left_list[LEFT_MENU_NUM];  // 左侧菜单数组
    int nowMenu = 0;  // 定位当前菜单
};

#endif // WIDGET_H

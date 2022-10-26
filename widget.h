#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <DBlurEffectWidget>
#include <DTitlebar>
#include <QPushButton>

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

public:
    bool themeIsDark;

private:
    Ui::Widget *ui;
    DTitlebar *titlebar;
    QPushButton * left_list[7];

private:
    void initUI();  // 初始化界面
};

#endif // WIDGET_H

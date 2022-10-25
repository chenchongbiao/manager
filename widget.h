#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <DBlurEffectWidget>
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

private:
    Ui::Widget *ui;
    void initUI();  // 初始化界面
};

#endif // WIDGET_H

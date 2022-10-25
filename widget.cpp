#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    DBlurEffectWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initUI()
{
    // ui初始化
    setMaskAlpha(200);  // 设置模糊窗口的不透明度，数值越低越通透
    ui->stackedWidget->setCurrentIndex(0);
}

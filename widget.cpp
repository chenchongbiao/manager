#include "widget.h"
#include "ui_mainwindow.h"

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

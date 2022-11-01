#include "homepagestatus.h"
#include "ui_homepagestatus.h"

#include <QGraphicsOpacityEffect>

HomePageStatus::HomePageStatus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomePageStatus)
{
    ui->setupUi(this);
    initUI();
}

HomePageStatus::~HomePageStatus()
{
    delete ui;
}

void HomePageStatus::initUI()
{
    // 初始化分界线
    ui->line1_widget->setStyleSheet("background-color:#808080");
    QGraphicsOpacityEffect *opacityEffect_1 = new QGraphicsOpacityEffect;
    opacityEffect_1->setOpacity(0.1);
    ui->line1_widget->setGraphicsEffect(opacityEffect_1);
}

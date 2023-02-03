#include "mlistwidget.h"
#include "ui_mlistwidget.h"

MListWidget::MListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MListWidget)
{
    ui->setupUi(this);
    initUI();
}

MListWidget::~MListWidget()
{
    delete ui;
}

void MListWidget::initUI()
{

}

DFrame* MListWidget::getOpDrm()
{
    return ui->opDfrm;
}

DFrame* MListWidget::getColDrm()
{
    return ui->colDfm;
}

QListWidget* MListWidget::getListWidget()
{
    return ui->listWdg;
}


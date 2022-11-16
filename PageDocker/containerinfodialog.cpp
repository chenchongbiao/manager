#include "containerinfodialog.h"
#include "ui_containerinfodialog.h"

ContainerInfoDialog::ContainerInfoDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContainerInfoDialog)
{
    ui->setupUi(this);
}

ContainerInfoDialog::~ContainerInfoDialog()
{
    delete ui;
}

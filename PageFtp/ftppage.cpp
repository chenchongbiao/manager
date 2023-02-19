#include "ftppage.h"
#include "ui_ftppage.h"

FtpPage::FtpPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FtpPage)
{
    ui->setupUi(this);
}

FtpPage::~FtpPage()
{
    delete ui;
}

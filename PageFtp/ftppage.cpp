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

void FtpPage::initUI()
{
    // 获取通用列表界面
    mlist = new MListWidget(this);

    // 搜索框及按钮部分初始化
    initOperationUI();
}

void FtpPage::initOperationUI()
{
    // 操作按钮布局
    opWdg = new QWidget(mlist->getOpDrm());
    opWdg->resize(mlist->getOpDrm()->width(),mlist->getOpDrm()->height());
    opLayout = new QHBoxLayout(opWdg);
    opLayout->setSpacing(6);          // 部件之间的间距
    opLayout->setContentsMargins(10, 0, 0, 0);   // 设置外边距
    opLayout->setAlignment(Qt::AlignLeft);


}

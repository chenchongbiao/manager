#include "pullimagedialog.h"
#include "ui_pullimagedialog.h"

PullImageDialog::PullImageDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PullImageDialog)
{
    ui->setupUi(this);
    initUI();
}

PullImageDialog::~PullImageDialog()
{
    delete ui;
}

void PullImageDialog::initUI()
{
    // 获取通用列表界面
    mlist = new MListWidget(this);

    opWdg = new QWidget(ui->opDfm);
    opWdgLayout = new QHBoxLayout(opWdg);
    opWdgLayout->setSpacing(6);
    opWdgLayout->setContentsMargins(6, 0, 0, 0); //  设置左侧、顶部、右侧和底部边距

    searchEdit = new DLineEdit();
    searchEdit->setFixedSize(200,45);
    searchEdit->setStyleSheet("background-color: #FFFFFF; border-radius: 5; border: 1px solid #E6E6E6; font-size:15px;");
    opWdgLayout->addWidget(searchEdit);

    searchBtn = new DPushButton("搜索");
    searchBtn->setFixedSize(60,ui->opDfm->height()-15);
    searchBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; font-size:15px;");
    opWdgLayout->addWidget(searchBtn);


}

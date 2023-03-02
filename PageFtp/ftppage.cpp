#include <QStringList>
#include <QDebug>

#include "ftppage.h"
#include "ui_ftppage.h"

FtpPage::FtpPage(QWidget *parent) :
    QWidget(parent)
//    ui(new Ui::FtpPage)
{
//    ui->setupUi(this);
    this->resize(parent->width(), parent->height());
//    this->setStyleSheet("background-color: black");
    initUI();
}

FtpPage::~FtpPage()
{
//    delete ui;
}

void FtpPage::initUI()
{
//    // 获取通用列表界面
//    mlist = new MListWidget(this);

//    // 搜索框及按钮部分初始化
//    initOperationUI();
//    QVBoxLayout *pVBoxLayout = new QVBoxLayout;
//    setLayout(pVBoxLayout);

//    QTableWidget *table = new QTableWidget(this);
//    table->resize(this->width(), this->height());
//    CheckBoxHeaderView *headerView = new CheckBoxHeaderView(QPoint(10, 5), QSize(20, 20), Qt::Horizontal, table);

//    table->setColumnCount(2);  // 设置列数
//    QStringList labelList;
//    labelList.insert(0, "");  // 在第一个位置插入空字符串给复选框占位置，否则第一个标签会和复选框重叠
//    labelList << "" << "测试";
//    table->setHorizontalHeaderLabels(labelList);  // 设置标签
//    table->setHorizontalHeader(headerView);
//    table->setColumnWidth(0, 20);  // 设置第0列，复选框的宽度
//    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);  // 设置第0列，复选框的宽度固定
//    table->setRowCount(1);  // 设置数据条数

//    pVBoxLayout->addWidget(tableView);
//    qDebug() << "[" << __FUNCTION__ <<__LINE__ << "] :" <<  this->width();

    MultiSelectList *multiSelectList = new MultiSelectList(this);
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

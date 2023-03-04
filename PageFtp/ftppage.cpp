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

    DLineEdit *lineEdit = new DLineEdit();
    DPushButton *searchBtn = new DPushButton("搜索");
    DPushButton *addFtpBtn = new DPushButton("添加Ftp");
    QStringList labelList;

    lineEdit->setPlaceholderText("请输入FTP用户名");
    lineEdit->setFixedWidth(200);

    searchBtn->setFixedSize(60,35);
    searchBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; font-size:15px;");
    //    connect(searchBtn,&QPushButton::clicked,this,&Container::SearchContainer);

    addFtpBtn->setFixedSize(70,35);
    addFtpBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; font-size:15px;");
    connect(addFtpBtn, &DPushButton::clicked, this, &FtpPage::addUserDialog);

    labelList << "用户名"
              << "密码"
              << "状态"
              << "根目录"
              << "备注"
              << "操作";

    multiSelectList->addOpLineEdit(lineEdit);
    multiSelectList->addOpButton(searchBtn);
    multiSelectList->addOpButton(addFtpBtn);

    multiSelectList->setColumnCount(6);  // 设置列数
    multiSelectList->setHeaderLabels(labelList);  // 设置标签
    multiSelectList->setHeader(multiSelectList->getHeader());
}

void FtpPage::addUserDialog()
{
    qDebug() << "[" << __FUNCTION__ <<__LINE__ << "] :"  <<  "打开添加Ftp用户的对话框";
    DDialog *dialog = new DDialog(this);
    DWidget *widget = new DWidget(dialog);

    QFormLayout *layout = new QFormLayout(widget);

    DLineEdit *userName = new DLineEdit();
    DLineEdit *passwd = new DLineEdit();
    DFileChooserEdit *chooserEdit = new DFileChooserEdit();

    chooserEdit->setFileMode(QFileDialog::Directory);  // 指定选择的模式 目录的名称。 显示文件和目录。
    chooserEdit->setDirectoryUrl(QUrl("file://" + QDir::homePath()));
    qDebug() << "[" << __FUNCTION__ <<__LINE__ << "] :"  << chooserEdit->fileDialog();

    dialog->addButton("取消", false, DDialog::ButtonNormal);
    dialog->addButton("确定", true, DDialog::ButtonRecommend);
    dialog->addContent(widget);

    layout->addRow("用户名", userName);
    layout->addRow("密码", passwd);
    layout->addRow("根目录", chooserEdit);

    layout->setContentsMargins(10, 5, 10, 5);
    layout->setSpacing(10);

    dialog->exec(); //显示对话框


//    Dtk::Widget::moveToCenter(dialog);
}

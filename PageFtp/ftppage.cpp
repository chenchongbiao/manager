#include <QStringList>
#include <QDebug>
#include <QTemporaryFile>
#include <DPasswordEdit>
#include <QSqlQuery>
#include <dboxwidget.h>
#include <DLabel>
#include <DLineEdit>
#include <DPushButton>

#include "ftppage.h"
#include "ui_ftppage.h"
#include "Utils/utils.h"

FtpPage::FtpPage(QWidget *parent) :
    QWidget(parent)
//    ui(new Ui::FtpPage)
{
//    ui->setupUi(this);
    this->resize(parent->width(), parent->height());
//    this->setStyleSheet("background-color: black");

    sqliteDB = new QSqlDatabase(QSqlDatabase::database("sqlite"));
    query = new QSqlQuery(*sqliteDB);

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
    DPushButton *addFtpBtn = new DPushButton("添加");
    DPushButton *delFtpBtn = new DPushButton("删除");
    QStringList labelList;

    lineEdit->setPlaceholderText("请输入FTP用户名");
    lineEdit->setFixedWidth(200);

    searchBtn->setFixedSize(60,35);
    searchBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; font-size:15px;");
    //    connect(searchBtn,&QPushButton::clicked,this,&Container::SearchContainer);

    addFtpBtn->setFixedSize(60,35);
    addFtpBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; font-size:15px;");
    connect(addFtpBtn, &DPushButton::clicked, this, &FtpPage::addUserDialog);

    delFtpBtn->setFixedSize(60, 35);
    delFtpBtn->setStyleSheet("color: #FFFFFF; background-color: #F56C6C; border-radius: 5; border: 0px; height: 30px; width: 30px; font-size:15px;");
    connect(delFtpBtn, &DPushButton::clicked, this, [=](){

    });

    labelList << "用户名"
              << "密码"
//              << "状态"
              << "根目录"
              << "备注"
              << "操作";

    multiSelectList->addOpLineEdit(lineEdit);
    multiSelectList->addOpButton(searchBtn);
    multiSelectList->addOpButton(addFtpBtn);
    multiSelectList->addOpButton(delFtpBtn);

    multiSelectList->setColumnCount(5);  // 设置列数
    multiSelectList->setHeaderLabels(labelList);  // 设置标签
//    multiSelectList->setHeader(multiSelectList->getHeader());  // 设置表头


    query->exec("SELECT user_name, passwd, root_path FROM ftp_user");
    // 这里使用query->size()返回结果为-1，后续查找原因
    int rowCount = 0;

    while (query->next()) {
        rowCount++;
        multiSelectList->setRowCount(rowCount);

        QString userName = query->value(0).toString();
        QString passwd = query->value(1).toString();
        QString rootPath = query->value(2).toString();
        qDebug() << userName << passwd << rootPath;

        DHBoxWidget *boxWidget = new DHBoxWidget();
        QCheckBox *box = new QCheckBox(boxWidget);
        DLabel *userNameLabel = new DLabel();
        DLineEdit *passwdEdit = new DLineEdit();
        DLabel *rootPathLabel = new DLabel();
        DHBoxWidget *opWidget = new DHBoxWidget();
        DPushButton *updatePasswdBtn = new DPushButton("改密");
        DPushButton *delUserBtn = new DPushButton("删除");

        boxWidget->addWidget(box);
        boxWidget->layout()->setMargin(0);
        boxWidget->layout()->setAlignment(box, Qt::AlignCenter);

        userNameLabel->setText(userName);

        passwdEdit->setText(passwd);
//        passwdEdit->setEnabled(false);
        passwdEdit->setEchoMode(QLineEdit::Password);
        passwdEdit->setPlaceholderText(passwd);

        rootPathLabel->setText(rootPath);

        updatePasswdBtn->setFixedSize(60,35);
        updatePasswdBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; font-size:15px;");
        delUserBtn->setFixedSize(60,35);
        delUserBtn->setStyleSheet("color: #FFFFFF; background-color: #F56C6C; border-radius: 5; border: 0px; font-size:15px;");
        opWidget->layout()->setSpacing(5);
        opWidget->addWidget(updatePasswdBtn);
        opWidget->addWidget(delUserBtn);

        multiSelectList->getTable()->setCellWidget(rowCount-1, 0, boxWidget);
        multiSelectList->getTable()->setCellWidget(rowCount-1, 1, userNameLabel);
        multiSelectList->getTable()->setCellWidget(rowCount-1, 2, passwdEdit);
        multiSelectList->getTable()->setCellWidget(rowCount-1, 3, rootPathLabel);
        multiSelectList->getTable()->setCellWidget(rowCount-1, 4, new DLabel("无"));
        multiSelectList->getTable()->setCellWidget(rowCount-1, 5, opWidget);
        multiSelectList->getTable()->setRowHeight(rowCount-1, 45);
    }

    qDebug() << "[" << __FUNCTION__ <<__LINE__ << "] :" << "读取ftp_user数据表" << rowCount;
}

void FtpPage::addUserDialog()
{
    qDebug() << "[" << __FUNCTION__ <<__LINE__ << "] :"  <<  "打开添加Ftp用户的对话框";
    DDialog *dialog = new DDialog(this);
    DWidget *widget = new DWidget(dialog);

    QFormLayout *layout = new QFormLayout(widget);

    DLineEdit *userName = new DLineEdit();
    DPasswordEdit *passwd = new DPasswordEdit();
    DFileChooserEdit *chooserEdit = new DFileChooserEdit();

    // 如果ftp用户的数据表不存在则创建。
    query->exec("CREATE TABLE IF NOT EXISTS ftp_user (id INTEGER PRIMARY KEY, user_name TEXT, passwd TEXT, root_path TEXT)");

    connect(userName, &DLineEdit::textChanged, this, [=](const QString &arg1){
        // 监听用户名文本框 修改根目录的路径 拼接成新路径
        QString path = chooserEdit->directoryUrl().url().split("file://").at(1);
        chooserEdit->setText(QString("%1/%2").arg(path).arg(arg1));
    });

    connect(chooserEdit, &DFileChooserEdit::fileChoosed, this, [=](){
        // 当选定根目录，拼接用户名成为根目录
        QString path = chooserEdit->directoryUrl().url().split("file://").at(1);
        chooserEdit->setText(QString("%1/%2").arg(path).arg(userName->text()));
    });

    chooserEdit->setFileMode(QFileDialog::Directory);  // 指定选择的模式 目录的名称。 显示文件和目录。
    chooserEdit->setText("/home");  // 默认在home目录添加新用户
    chooserEdit->setDirectoryUrl(QUrl("file:///home"));
    qDebug() << "[" << __FUNCTION__ <<__LINE__ << "] :"  << chooserEdit->fileDialog();

    dialog->addButton("取消", false, DDialog::ButtonNormal);
    dialog->addButton("确定", true, DDialog::ButtonRecommend);
    connect(dialog->getButton(1), &DPushButton::clicked, this, [=, this](){
        QString filePath = QString("%1/ftp_%2").arg(QDir::tempPath()).arg(userName->text());
        QString userPasswd = QString("%1:%2").arg(userName->text()).arg(passwd->text());

        QTemporaryFile tmpFile(filePath);  // 创建QTemporaryFile 对象保存文件
        if( tmpFile.open() )
        {
            tmpFile.write(userPasswd.toUtf8());  // 将QString转QByteArray
            tmpFile.close();
        }

        Utils::sudo(QString("useradd -m -d %1 %2;").arg(chooserEdit->text()).arg(userName->text()));
        Utils::sudo(QString("chpasswd < %1").arg(tmpFile.fileName()));

        // 在sqlite中插入数据
        query->prepare("INSERT INTO ftp_user (user_name, passwd, root_path) VALUES (:user_name, :passwd, :root_path)");
        query->bindValue(":user_name", userName->text());
        query->bindValue(":passwd", passwd->text());
        query->bindValue(":root_path", chooserEdit->text());
        query->exec();

        qDebug() << tmpFile.fileName();
    });

    dialog->addContent(widget);

    layout->addRow("用户名", userName);
    layout->addRow("密码", passwd);
    layout->addRow("根目录", chooserEdit);

    layout->setContentsMargins(10, 5, 10, 5);
    layout->setSpacing(10);

    dialog->exec(); //显示对话框
}

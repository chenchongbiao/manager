#include "network.h"
#include "ui_network.h"

Network::Network(QWidget *parent) :
    QWidget(parent)
//    ui(new Ui::Network)
{
//    ui->setupUi(this);
    initUI();
}

Network::~Network()
{
//    delete ui;
}

void Network::initUI()
{
    // 通用列表界面
    mlist = new MListWidget(this);

    // 初始化操作栏
    initOperationUI();

    // 列名初始化
    initColumnUI();
}

void Network::initOperationUI()
{
    netBtnWidget = new QWidget(mlist->getBtnDrm());
    netBtnWidget->resize(mlist->getBtnDrm()->width(),mlist->getBtnDrm()->height());
    netBtnLayout = new QHBoxLayout(netBtnWidget);
    netBtnLayout->setSpacing(6); // 部件之间的间距
    netBtnLayout->setContentsMargins(10, 0, 0, 0);  // 设置上下左右的间距
    netBtnLayout->setAlignment(Qt::AlignLeft);

    searchEdit = new DLineEdit();
    searchEdit->setFixedWidth(200);
    searchEdit->setPlaceholderText("请输入网络名");
    netBtnLayout->addWidget(searchEdit);

    searchBtn = new DPushButton("搜索");
    searchBtn->setFixedSize(60,35);
    searchBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; font-size:15px;");
    connect(searchBtn, &QPushButton::clicked, this, &Network::SearchContainer);
    netBtnLayout->addWidget(searchBtn);

    createBtn = new DPushButton("创建");
    createBtn->setFixedSize(60,35);
    createBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; font-size:15px;");
    connect(createBtn,&DPushButton::clicked,this,&Network::OpenCreateNetDialog);
    netBtnLayout->addWidget(createBtn);
}

void Network::initColumnUI()
{
    QString labStyle = "font-size:15px;";
    int labWidth = 110; // id标签的宽度
    int operationLabWidth = 150;  // 操作部分的标签宽度
    columnWidget = new QWidget(mlist->getColDrm());
    columnLayout = new QHBoxLayout(columnWidget);
    columnLayout->setContentsMargins(10, 0, 0, 0);  // 设置外边距
    columnLayout->setSpacing(0); // 设置部件的间距

    checkAllBtn = new QCheckBox(columnWidget);
    checkAllBtn->setFixedSize(mlist->getBtnDrm()->height()-20,mlist->getBtnDrm()->height());
    connect(checkAllBtn,&QCheckBox::clicked,this,&Network::CheckAllNetwork);
    columnLayout->addWidget(checkAllBtn);

    // 定义一个函数，用来添加表头，依次传入，表头名称，以及宽度
    auto addColumnItem = [&](const QString labName, const int labWidth){
        DLabel *label = new DLabel(labName);
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet(labStyle);
        label->setFixedWidth(labWidth);
        columnLayout->addWidget(label);
    };

    addColumnItem("ID", labWidth);
    addColumnItem("名称", labWidth);
    addColumnItem("驱动类型", labWidth);
    addColumnItem("连接容器数量", labWidth);
    addColumnItem("操作", operationLabWidth);
}

void Network::CheckAllNetwork()
{
    if (checkAllBtn->isChecked())
    {
        qDebug() << "全选按钮被点击";
        for(int i=0;i < mlist->getListWidget()->count();i++)
        {
            QWidget *curNetwork = mlist->getListWidget()->itemWidget(mlist->getListWidget()->item(i));
            QCheckBox *checkBox = curNetwork->findChildren<QCheckBox*>().at(0);
            if (checkBoxBtnList.indexOf(checkBox) == -1)  // 等于-1表示没被选中
            {
                checkBox->setChecked(true);
                checkBoxBtnList.append(checkBox);
            }

        }
    } else {
        qDebug() << "全选按钮取消";
        for(QCheckBox *checkBox: checkBoxBtnList)
        {
            checkBox->setChecked(false);
        }
        checkBoxBtnList.clear();
    }
}

void Network::SearchContainer()
{
    qDebug() << "搜索网络按钮被点击";
    QString keyword = searchEdit->text();
}
void Network::OpenCreateNetDialog()
{
    qDebug() << "打开创建网络窗口 ";
    DDialog *dialog = new DDialog;
    dialog->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose); //将指针设置为窗口关闭即释放
    dialog->exec(); //显示对话框
}

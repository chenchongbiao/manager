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

    // 从sessionbus中
    networkArray = DBusClient::GetNetworkList();

    // 初始化网络列表
    initNetworkListUI();
}

void Network::initOperationUI()
{
    netBtnWidget = new QWidget(mlist->getOpDrm());
    netBtnWidget->resize(mlist->getOpDrm()->width(),mlist->getOpDrm()->height());
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
    int labWidth = 110; // 标签的宽度
    int operationLabWidth = 150;  // 操作部分的标签宽度
    columnWidget = new QWidget(mlist->getColDrm());
    columnLayout = new QHBoxLayout(columnWidget);
    columnLayout->setContentsMargins(10, 0, 0, 0);  // 设置外边距
    columnLayout->setSpacing(0); // 设置部件的间距

    checkAllBtn = new QCheckBox(columnWidget);
    checkAllBtn->setFixedSize(mlist->getOpDrm()->height()-20,mlist->getOpDrm()->height());
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

void Network::initNetworkListUI()
{
    QString labStyle = "font-size:15px;";
    int labWidth = 110; // 标签的宽度
    int operationLabWidth = 150;  // 操作部分的标签宽度

    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(networkArray, &jsonError);  // 转化为 JSON 文档
    if (!document.isNull() && (jsonError.error == QJsonParseError::NoError)) { // 解析未发生错误
        if (document.isObject()) {  // JSON 文档为对象
            QJsonObject object = document.object();  // 转化为对象
            if (object.contains("data")) {  // 包含指定的 key
                QJsonValue dataValue = object.value("data");  // 获取指定 key 对应的 value
                if (dataValue.isArray()) { // JSON 文档为数组
                    QJsonArray networkJson = dataValue.toArray();
                    int netSize = networkJson.size();
                    for (int i = 0; i < netSize; i++) {
                        QJsonValue value = networkJson.at(i);      // 取出单个json
                        QJsonObject obj = value.toObject();        // 转换为object

                        QWidget *networkWdg = new QWidget(mlist->getListWidget());
                        QHBoxLayout *layout = new QHBoxLayout(networkWdg);
                        layout->setMargin(0);  // 设置外边距

                        QCheckBox *checkBtn = new QCheckBox(mlist->getListWidget());
                        checkBtn->setFixedSize(mlist->getOpDrm()->height()-20,mlist->getOpDrm()->height());
                        layout->addWidget(checkBtn);
                        connect(checkBtn,&QCheckBox::clicked, this, &Network::CheckNetwork);

                        // 定义一个函数，用来添加表头，依次传入，表头名称，以及宽度
                        auto addNetworkItem = [&](const QString labName, const int labWidth){
                            DLabel *label = new DLabel(labName);
                            label->setAlignment(Qt::AlignCenter);
                            label->setStyleSheet(labStyle);
                            label->setFixedWidth(labWidth);
                            layout->addWidget(label);
                        };

                        // 获取网络id
                        QString id = obj.value("id").toString().left(10);
                        addNetworkItem(id, labWidth);

                        // 获取网络名称
                        QString name = obj.value("name").toString();
                        addNetworkItem(name, labWidth);

                        // 获取网络名称
                        QString driver = obj.value("driver").toString();
                        if (!driver.isEmpty())
                        {
                            if (driver == "null")
                            {
                                driver = "(无)";
                            } else if (driver == "host") {
                                driver = "主机";
                            } else if (driver == "bridge") {
                                driver = "网桥";
                            }

                        }
                        addNetworkItem(driver, labWidth);

                        // 获取连接的容器数量
                        qint64 countContainer = obj.value("container_num").toInt();
                        addNetworkItem(QString("%1").arg(countContainer), labWidth);

                        // 生成操作栏
                        QWidget *operationWidget = new QWidget(networkWdg);
                        operationWidget->resize(50, mlist->getOpDrm()->height());
                        QHBoxLayout *operationLayout = new QHBoxLayout(operationWidget);
                        operationLayout->setContentsMargins(10, 0, 0, 0);  //  设置左侧、顶部、右侧和底部边距，

                        DPushButton *infoBtn = new DPushButton("信息");
                        infoBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; height: 30px; font-size:13px;");
                        connect(infoBtn,&QPushButton::clicked,this,[=](){});
                        operationLayout->addWidget(infoBtn);

                        DPushButton *delBtn = new DPushButton("删除");
                        delBtn->setStyleSheet("color: #FFFFFF; background-color: #F56C6C; border-radius: 5; border: 0px; height: 30px; font-size:13px;");
                        connect(delBtn,&DPushButton::clicked,this,[=](){});
                        operationLayout->addWidget(delBtn);

                        DPushButton *operationBtn = new DPushButton("操作");
                        operationBtn->setStyleSheet("color: #FFFFFF; background-color: #1E90FF; border-radius: 5; border: 0px; height: 30px; font-size:13px;");
                        operationBtn->setCheckable(true);
                        QMenu *operationMenu = new QMenu(operationWidget);
                        QAction *action = operationMenu->addAction("item_1");
                        connect(action ,&QAction::triggered ,this ,[=](){
                                //里面写点击后执行的函数就行

                        });
                        operationMenu->addAction("item_2");
                        operationMenu->addAction("item_3");
                        operationBtn->setMenu(operationMenu);
                        operationLayout->addWidget(operationBtn);
                        layout->addWidget(operationWidget);

                        QListWidgetItem *networkItem=new QListWidgetItem(mlist->getListWidget());
                        networkItem->setSizeHint(QSize(40,40));
                        networkItem->setFlags(Qt::ItemIsSelectable); // 取消选择项
                        mlist->getListWidget()->setItemWidget(networkItem, networkWdg);  // 将networkWdg赋予networkItem
                    }
                }
            }
        }

    }
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

void Network::CheckNetwork()
{

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

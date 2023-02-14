#include "pullimagedialog.h"
#include "ui_pullimagedialog.h"

PullImageDialog::PullImageDialog(QWidget *parent) :
    QWidget(parent)
//    ui(new Ui::PullImageDialog)
{
//    ui->setupUi(this);
    initUI();
}

PullImageDialog::~PullImageDialog()
{
//    delete ui;
}

void PullImageDialog::initUI()
{
    // 获取通用列表界面
    mlist = new MListWidget(this);
    this->setFixedSize(mlist->width(),mlist->height());

    // 初始化操作栏的UI
    initOperationUI();

    // 初始化列名的UI
    initColumnUI();
}

void PullImageDialog::initOperationUI()
{
    opWdg = new QWidget(mlist->getOpDrm());
    opWdgLayout = new QHBoxLayout(opWdg);
    opWdgLayout->setSpacing(6);
    opWdgLayout->setContentsMargins(6, 0, 0, 0); //  设置左侧、顶部、右侧和底部边距

    searchEdit = new DLineEdit();
    searchEdit->setFixedSize(200,45);
    searchEdit->setStyleSheet("background-color: #FFFFFF; border-radius: 5; border: 1px solid #E6E6E6; font-size:15px;");
    opWdgLayout->addWidget(searchEdit);

    searchBtn = new DPushButton("搜索");
    searchBtn->setFixedSize(60,35);
    searchBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; font-size:15px;");
    connect(searchBtn,&QPushButton::clicked,this,&PullImageDialog::SearchImageFromHub);
    opWdgLayout->addWidget(searchBtn);
}

void PullImageDialog::initColumnUI()
{
    QString labStyle = "font-size:15px;";
    int nameLabWidth = 200;
    int dscrpLabWidth = 200;
    int starLabWidth = 100;
    int officialLabWidth = 100;
    int automatedLabWidth = 100;
    columnWdg = new QWidget(mlist->getColDrm());
    columnLayout = new QHBoxLayout(columnWdg);
    columnLayout->setContentsMargins(0, 10, 0, 0);  //  设置左侧、顶部、右侧和底部边距
    columnLayout->setSpacing(0);  // 部件之间的间距

    // 定义一个函数，用来添加表头，依次传入，表头名称，以及宽度
    auto addColumnItem = [&](const QString labName, const int labWidth){
        DLabel *label = new DLabel(labName);
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet(labStyle);
        label->setFixedWidth(labWidth);
        columnLayout->addWidget(label);
    };

    addColumnItem("名称", nameLabWidth);
    addColumnItem("描述", dscrpLabWidth);
    addColumnItem("Star数", starLabWidth);
    addColumnItem("官方镜像", officialLabWidth);
    addColumnItem("自动构建", automatedLabWidth);
}

void PullImageDialog::initImageListUI()
{
    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(imageArray, &jsonError);  // 转化为 JSON 文档
    if (!document.isNull() && (jsonError.error == QJsonParseError::NoError)) { // 解析未发生错误
        if (document.isObject()) {  // JSON 文档为对象
            QJsonObject object = document.object();  // 转化为对象
            if (object.contains("data")) {  // 包含指定的 key
                QJsonValue dataValue = object.value("data");  // 获取指定 key 对应的 value

                if (dataValue.isArray()) { // JSON 文档为数组
                    QJsonArray imageJson = dataValue.toArray();
                    int conSize = imageJson.size();
                    for (int i = 0; i < conSize; i++) {
                        QJsonValue value = imageJson.at(i);      // 取出单个json
                        QJsonObject obj = value.toObject();           // 转换为object

                        QWidget *listWidget = new QWidget(mlist->getListWidget());  // 主页软件单条数据控件

                        QHBoxLayout *layout = new QHBoxLayout(listWidget);
                        layout->setMargin(0);  //  设置外边距，左侧、顶部、右侧和底部边距，

                        QString name = obj.value("name").toString();
                        DLabel *nameLab = new DLabel(name);
                        nameLab->setAlignment(Qt::AlignCenter);
                        nameLab->setFixedWidth(200);
                        layout->addWidget(nameLab);

                        QString dscrp = obj.value("description").toString();
                        DLabel *dscrpLab = new DLabel(dscrp);
                        dscrpLab->setAlignment(Qt::AlignCenter);
                        dscrpLab->setFixedWidth(150);
                        layout->addWidget(dscrpLab);

                        QString star = QString("%1").arg(obj.value("star_count").toInt());
                        DLabel *starLab = new DLabel(star);
                        starLab->setAlignment(Qt::AlignCenter);
                        starLab->setFixedWidth(100);
                        layout->addWidget(starLab);

                        bool isOfficial = obj.value("is_official").toBool();
                        QString official = "";
                        if (isOfficial) {
                            official = "是";
                        } else {
                            official = "否";
                        }
                        DLabel *officialLab = new DLabel(official);
                        officialLab->setAlignment(Qt::AlignCenter);
                        officialLab->setFixedWidth(100);
                        layout->addWidget(officialLab);


                        bool isAutomated = obj.value("is_automated").toBool();
                        QString automated = "";
                        if (isAutomated) {
                            automated = "支持";
                        } else {
                            automated = "不支持";
                        }
                        DLabel *automateLab = new DLabel(automated);
                        automateLab->setAlignment(Qt::AlignCenter);
                        automateLab->setFixedWidth(100);
                        layout->addWidget(automateLab);

                        QListWidgetItem *imageItem=new QListWidgetItem(mlist->getListWidget());
                        imageItem->setSizeHint(QSize(40,40));
        //                containerItem->setToolTip(); // 提示框
//                        imageItem->setFlags(Qt::ItemIsSelectable); // 取消选择项
                        mlist->getListWidget()->setItemWidget(imageItem,listWidget);  // 将dockerWidgetr赋予containerItem
                    }
                }
            }
        }
    }
}

void PullImageDialog::ReInitContainerList()
{
    mlist->getListWidget()->clear();                // 清除控件
    initImageListUI();                              // 重新生成容器列表
}

void PullImageDialog::SearchImageFromHub()
{
    qDebug() << "搜索容器按钮被点击";
    QString keyword = searchEdit->text();
    if (keyword == "") {
        qDebug() << "容器名为空";
        DMessageManager::instance()->sendMessage(this, style()->standardIcon(QStyle::SP_MessageBoxWarning),"容器名为空");
    } else {
//        QMap<QString,QVariant> args;
//        args.insert("name", keyword);
        imageArray = DBusClient::SearchImageFromHub(keyword);  // 获取所有容器数据
        ReInitContainerList();  // 绘制列表
        DMessageManager::instance()->sendMessage(this, style()->standardIcon(QStyle::SP_MessageBoxWarning),"搜索成功");
    }
}

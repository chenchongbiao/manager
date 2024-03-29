#include "volume.h"4
Volume::Volume(QWidget *parent) :
    QWidget(parent)
{
    initUI();
}

void Volume::initUI()
{
    // 通用列表界面
    mlist = new MListWidget(this);

    // 初始化操作栏
    initOperationUI();

    // 列名初始化
    initColumnUI();

    // 从sessionbus中获取数据
    volumeArray = DBusClient::GetVolumeList(QMap<QString,QVariant>());

    // 初始化存储器列表
    initVolumeListUI();
}

void Volume::initOperationUI()
{
    opWdg = new QWidget(mlist->getOpDrm());
    opWdg->resize(mlist->getOpDrm()->width(),mlist->getOpDrm()->height());
    opLayout = new QHBoxLayout(opWdg);
    opLayout->setSpacing(6);
    opLayout->setContentsMargins(10, 0, 0, 0);
    opLayout->setAlignment(Qt::AlignLeft);

    searchEdit = new DLineEdit();
    searchEdit->setFixedWidth(200);
    searchEdit->setPlaceholderText("请输入存储卷名");
    opLayout->addWidget(searchEdit);

    searchBtn = new DPushButton("搜索");
    searchBtn->setFixedSize(60, 35);
    searchBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; font-size:15px;");
    connect(searchBtn, &DPushButton::clicked, this, &Volume::SearchVolume);
    opLayout->addWidget(searchBtn);

    createBtn = new DPushButton("创建");
    createBtn->setFixedSize(60,35);
    createBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; font-size:15px;");
    connect(createBtn,&DPushButton::clicked,this,&Volume::OpenCreateVolDialog);
    opLayout->addWidget(createBtn);
}

void Volume::initColumnUI()
{
    QString labStyle = "font-size:15px;";
    int labWidth = 110; // 标签的宽度
    int operationLabWidth = 150;  // 操作部分的标签宽度
    colWdg = new QWidget(mlist->getColDrm());
    colLayout = new QHBoxLayout(colWdg);
    colLayout->setContentsMargins(10, 0, 0, 0);  // 设置外边距
    colLayout->setSpacing(0);  // 部件的间距

    checkAllBtn = new QCheckBox(colWdg);
    checkAllBtn->setFixedSize(mlist->getOpDrm()->height()-20,mlist->getOpDrm()->height());
    connect(checkAllBtn,&QCheckBox::clicked,this,&Volume::CheckAllVolume);
    colLayout->addWidget(checkAllBtn);

    // 定义一个函数，用来添加表头，依次传入，表头名称，以及宽度
    auto addColumnItem = [&](const QString labName, const int labWidth){
        DLabel *label = new DLabel(labName);
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet(labStyle);
        label->setFixedWidth(labWidth);
        colLayout->addWidget(label);
    };

    addColumnItem("名称", labWidth-50);
    addColumnItem("驱动器类型", labWidth-30);
    addColumnItem("挂载点", labWidth+90);
    addColumnItem("创建时间", labWidth);
    addColumnItem("操作", operationLabWidth);

}

void Volume::initVolumeListUI()
{
    QString labStyle = "font-size:15px;";
    int labWidth = 110; // 标签的宽度
    int operationLabWidth = 150;  // 操作部分的标签宽度

    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(volumeArray, &jsonError);  // 转化为 JSON 文档
    if (!document.isNull() && (jsonError.error == QJsonParseError::NoError)) { // 解析未发生错误
        if (document.isObject()) {  // JSON 文档为对象
            QJsonObject object = document.object();  // 转化为对象
            if (object.contains("data")) {  // 包含指定的 key
                QJsonValue dataValue = object.value("data");  // 获取指定 key 对应的 value
                if (dataValue.isArray()) { // JSON 文档为数组
                    QJsonArray volumeJson = dataValue.toArray();
                    int volSize = volumeJson.size();
                    for (int i = 0; i < volSize; i++) {
                        QJsonValue value = volumeJson.at(i);      // 取出单个json
                        QJsonObject obj = value.toObject();        // 转换为object

                        QWidget *volumeWdg = new QWidget(mlist->getListWidget());
                        QHBoxLayout *layout = new QHBoxLayout(volumeWdg);
                        layout->setMargin(0);  // 设置外边距

                        QCheckBox *checkBtn = new QCheckBox(mlist->getListWidget());
                        checkBtn->setFixedSize(mlist->getOpDrm()->height()-20,mlist->getOpDrm()->height());
                        layout->addWidget(checkBtn);
                        connect(checkBtn,&QCheckBox::clicked, this, &Volume::CheckVolume);

                        // 定义一个函数，用来添加表头，依次传入，表头名称，以及宽度
                        auto addNetworkItem = [&](const QString labName, const int labWidth){
                         DLabel *label = new DLabel(labName);
                         label->setAlignment(Qt::AlignCenter);
                         label->setStyleSheet(labStyle);
                         label->setFixedWidth(labWidth);
                         layout->addWidget(label);
                        };

                        // 获取存储卷名称
                        QString name = obj.value("name").toString();
                        addNetworkItem(name, labWidth-70);

                        // 获取驱动器类型
                        QString driver = obj.value("driver").toString();
                        addNetworkItem(driver, labWidth-60);

                        // 获取挂载点
                        QString mountPoint = obj.value("mount_point").toString();
                        addNetworkItem(mountPoint, labWidth+130);

                        // 创建时间
                        QString createTime = obj.value("create_time").toString().left(10);
                        addNetworkItem(createTime, labWidth);

                        // 生成操作栏
                        QWidget *operationWidget = new QWidget(volumeWdg);
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
                        mlist->getListWidget()->setItemWidget(networkItem, volumeWdg);  // 将networkWdg赋予networkItem


                    }
                }
            }
        }
    }
}

void Volume::ReInitVolumeList()
{
    mlist->getListWidget()->clear(); // 清除控件
    checkBoxBtnList.clear();
    checkAllBtn->setChecked(false);
    initVolumeListUI(); // 重新生成容器列表
}

void Volume::SearchVolume()
{
    qDebug() << "搜索存储卷按钮被点击";
    QString keyword = searchEdit->text();
    qDebug() << "存储卷名" << keyword;
    if (keyword == "") {
        qDebug() << "存储卷名为空";
        DMessageManager::instance()->sendMessage(this, style()->standardIcon(QStyle::SP_MessageBoxWarning),"容器名为空");
    } else {
        QMap<QString,QVariant> args;
        args.insert("name", keyword);
        volumeArray = DBusClient::GetVolumeList(args);  // 获取所有容器数据
        ReInitVolumeList();  // 绘制列表
        DMessageManager::instance()->sendMessage(this, style()->standardIcon(QStyle::SP_MessageBoxWarning),"搜索成功");
    }
}

void Volume::CheckAllVolume()
{
    if (checkAllBtn->isChecked())
    {
        qDebug() << "全选按钮被点击";
        for(int i=0;i < mlist->getListWidget()->count();i++)
        {
            QWidget *curContaier = mlist->getListWidget()->itemWidget(mlist->getListWidget()->item(i));
            QCheckBox *checkBox = curContaier->findChildren<QCheckBox*>().at(0);
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

void Volume::CheckVolume()
{
    QCheckBox *curBtn = (QCheckBox *) sender();// 槽函数中调用sender函数，返回指向发送信号的对象的指针
    int index = checkBoxBtnList.indexOf(curBtn);
    if (index == -1) // 等于-1代表没有被选中了，添加到QList中
    {
        qDebug() << "当前选中" << curBtn->parent()->findChildren<DLabel *>().at(0)->text();
        checkBoxBtnList.append(curBtn);
    } else {
        qDebug() << "当前取消" << curBtn->parent()->findChildren<DLabel *>().at(0)->text();
        checkBoxBtnList.removeAt(index);
    }
    if (checkBoxBtnList.count() == mlist->getListWidget()->count() && !checkAllBtn->isChecked()) // 所有数据都被选中 并且全选按钮未被选中
    {
        checkAllBtn->setChecked(true);
    } else if (checkBoxBtnList.count() != mlist->getListWidget()->count() && checkAllBtn->isChecked()){ // 所有数据未被选中 但是全选按钮被选中
        checkAllBtn->setChecked(false);
    }
}

void Volume::OpenCreateVolDialog()
{

}

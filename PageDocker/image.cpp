#include <DLineEdit>
#include <DPushButton>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusConnection>
#include <DMessageManager>
#include <QDateTime>
#include <QMenu>

#include "image.h"
#include "ui_image.h"
#include "Utils/utils.h"
#include "dbusclient.h"

Image::Image(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Image)
{
    ui->setupUi(this);
    initUI();
}

Image::~Image()
{
    delete ui;
}

void Image::initUI()
{
//    int width = ui->imgDfrm->width();
//    int height = ui->imgDfrm->height();

    mlist = new MListWidget(this);
    imgBtnWidget = new QWidget(mlist->getBtnDrm());
    imgBtnWidget->resize(mlist->getBtnDrm()->width(),mlist->getBtnDrm()->height());
    imgBtnLayout = new QHBoxLayout(imgBtnWidget);
    imgBtnLayout->setSpacing(6);  // 部件之间的间距
    imgBtnLayout->setContentsMargins(10, 0, 0, 0);  //  设置左侧、顶部、右侧和底部边距，
    imgBtnLayout->setAlignment(Qt::AlignLeft);

    searchEdit = new DLineEdit();
    searchEdit->setPlaceholderText("请输入镜像名");
    searchEdit->setFixedWidth(200);
    imgBtnLayout->addWidget(searchEdit);

    searchBtn = new DPushButton("搜索");
    searchBtn->setFixedSize(60,35);
    searchBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; font-size:15px;");
    connect(searchBtn,&DPushButton::clicked,this,&Image::SearchImage);
    imgBtnLayout->addWidget(searchBtn);

    deleteBtn = new DPushButton("删除");
    deleteBtn->setFixedSize(60,35);
    deleteBtn->setStyleSheet("color: #FFFFFF; background-color: #F56C6C; border-radius: 5; border: 0px; font-size:15px;");
    imgBtnLayout->addWidget(deleteBtn);

//    refreshBtn = new DPushButton("刷新");
//    refreshBtn->setFixedSize(60,35);
//    refreshBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; font-size:15px;");
//    imgBtnLayout->addWidget(refreshBtn);

    pullImageBtn = new DPushButton("拉取镜像");
    pullImageBtn->setFixedSize(80,35);
    pullImageBtn->setStyleSheet("color: #FFFFFF; background-color: #1E90FF; border-radius: 5; border: 0px; font-size:15px;");
    imgBtnLayout->addWidget(pullImageBtn);

    imgBtnLayout->addSpacing(10);

    columnWidget = new QWidget(mlist->getColDrm());
    columnLayout = new QHBoxLayout(columnWidget);
    columnLayout->setContentsMargins(10, 0, 0, 0);  //  设置左侧、顶部、右侧和底部边距，
    columnLayout->setSpacing(0);  // 部件之间的间距

    checkAllBtn = new QCheckBox(columnWidget);
    checkAllBtn->setFixedSize(mlist->getBtnDrm()->height()-20,mlist->getBtnDrm()->height());
    connect(checkAllBtn,&QCheckBox::clicked,this,&Image::CheckAllImage);
    columnLayout->addWidget(checkAllBtn);

    idLab = new DLabel("ID");
    idLab->setAlignment(Qt::AlignCenter);
    idLab->setFixedWidth(110);
    columnLayout->addWidget(idLab);

    tagsLab = new DLabel("标签");
    tagsLab->setAlignment(Qt::AlignCenter);
    tagsLab->setFixedWidth(130);
    columnLayout->addWidget(tagsLab);

    imageSizeLab = new DLabel("镜像尺寸");
    imageSizeLab->setAlignment(Qt::AlignCenter);
    imageSizeLab->setFixedWidth(80);
    columnLayout->addWidget(imageSizeLab);

    createTimeLab = new DLabel("创建时间");
    createTimeLab->setAlignment(Qt::AlignCenter);
    createTimeLab->setFixedWidth(110);
    columnLayout->addWidget(createTimeLab);

    operationLab = new DLabel("操作");
    operationLab->setAlignment(Qt::AlignCenter);
    operationLab->setFixedWidth(150);
    columnLayout->addWidget(operationLab);

    /*
     * 从sessionbus初始化镜像列表
    */
    imageArray = DBusClient::GetImageList();
    initImageListUI();
}

void Image::initImageListUI()
{
    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(imageArray,&jsonError);   // 转化为 JSON 文档
    if (!document.isNull() && (jsonError.error == QJsonParseError::NoError)) { // 解析未发生错误
        if (document.isObject()) {  // JSON 文档为对象
            QJsonObject object = document.object();  // 转化为对象
            if (object.contains("data")) {  // 包含指定的 key
                QJsonValue dataValue = object.value("data");  // 获取指定 key 对应的 value
                if (dataValue.isArray()) { // JSON 文档为数组
                    QJsonArray imageArray = dataValue.toArray();
                    int imgSize = imageArray.size();
                    for(int i=0;i < imgSize;i++) {
                        QJsonValue value = imageArray.at(i);
                        QJsonObject obj = value.toObject();

                        QWidget *imgWidget = new QWidget(mlist->getListWidget());  // 主页软件单条数据的widget
                        imgWidget->resize(mlist->getListWidget()->width(), mlist->getListWidget()->height());

                        QHBoxLayout *layout = new QHBoxLayout(imgWidget);
                        layout->setMargin(0);  //  设置设置外边距，左侧、顶部、右侧和底部边距，

                        QCheckBox *checkBtn = new QCheckBox(mlist->getListWidget());
                        checkBtn->setFixedSize(mlist->getBtnDrm()->height()-20, mlist->getBtnDrm()->height());
                        layout->addWidget(checkBtn);
                        connect(checkBtn,&QCheckBox::clicked, this, &Image::CheckImage);

                        QString id = obj.value("id").toString().left(12);
                        DLabel *imgId = new DLabel(id);
                        imgId->setAlignment(Qt::AlignCenter);
                        imgId->setFixedWidth(110);
                        layout->addWidget(imgId);

                        QString RepoTags = obj.value("tags").toArray().at(0).toString();
                        DLabel *tags = new DLabel(RepoTags);
                        tags->setAlignment(Qt::AlignCenter);
                        tags->setFixedWidth(130);
                        layout->addWidget(tags);

                        qint64 size = obj.value("size").toInt();
                        DLabel *imgSize = new DLabel(QString("%1").arg(Utils::formatSize(size)));
                        imgSize->setFixedWidth(80);
                        layout->addWidget(imgSize);

                        qint64 createTime = obj.value("create_time").toInt();
                        QString dateTime = QDateTime::fromSecsSinceEpoch(createTime).toString("yyyy-MM-dd hh:mm:ss");
                        DLabel *dockerName = new DLabel(dateTime);
                        dockerName->setFixedWidth(120);
                        layout->addWidget(dockerName);

                        QWidget *operationWidget = new QWidget(imgWidget);
                        operationWidget->resize(150,mlist->getBtnDrm()->height());
                        QHBoxLayout *operationLayout = new QHBoxLayout(operationWidget);
                        operationLayout->setContentsMargins(10, 0, 0, 0);  //  设置左侧、顶部、右侧和底部边距，
                        DPushButton *infoBtn = new DPushButton("信息");
                        infoBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; height: 30px; width: 30px; font-size:13px;");
                        operationLayout->addWidget(infoBtn);

                        DPushButton *delBtn = new DPushButton("删除");
                        delBtn->setStyleSheet("color: #FFFFFF; background-color: #F56C6C; border-radius: 5; border: 0px; height: 30px; width: 30px; font-size:13px;");
                        operationLayout->addWidget(delBtn);
                        layout->addWidget(operationWidget);

                        DPushButton *operationBtn = new DPushButton("操作");
                        operationBtn->setStyleSheet("color: #FFFFFF; background-color: #1E90FF; border-radius: 5; border: 0px; height: 30px; width: 30px; font-size:13px;");
                        operationBtn->setCheckable(true);
                        QMenu *operationMenu = new QMenu(this);
                        QAction *action = operationMenu->addAction("item_1");
                        connect(action ,&QAction::triggered ,this ,[=](){
                                //里面写点击后执行的函数就行

                        });
                        operationMenu->addAction("item_2");
                        operationMenu->addAction("item_3");
                        operationBtn->setMenu(operationMenu);
                        operationLayout->addWidget(operationBtn);

                        QListWidgetItem *containerItem=new QListWidgetItem(mlist->getListWidget());
                        containerItem->setSizeHint(QSize(40,40));
                        //  containerItem->setToolTip(); // 提示框
                        containerItem->setFlags(Qt::ItemIsSelectable); // 取消选择项
                        mlist->getListWidget()->setItemWidget(containerItem,imgWidget);  // 将dockerWidgetr赋予containerItem
                    }
                }
            }
        }
    }
}

void Image::CheckImage()
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

void Image::CheckAllImage()
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

void Image::SearchImage()
{
    qDebug() << "搜索镜像按钮被点击";
    QString keyword = searchEdit->text();
    qDebug() << "镜像名" << keyword;
    imageArray = DBusClient::SearchImageByName(keyword);
    if (imageArray.isEmpty()) {
        qDebug() << "镜像数据为空";
        imageArray = DBusClient::GetImageList();
    }
    mlist->getListWidget()->clear();    // 清除控件
    initImageListUI();       // 重新获取镜像数据
}

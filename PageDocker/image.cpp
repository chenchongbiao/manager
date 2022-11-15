#include <DLineEdit>
#include <DPushButton>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusConnection>
#include <DMessageManager>

#include "image.h"
#include "ui_image.h"

Image::Image(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Image)
{
    ui->setupUi(this);
    GetImageArrayFromSessionBus();  // 调用sessionbus获取容器列表数据
    initUI();
}

Image::~Image()
{
    delete ui;
}

void Image::initUI()
{
    int width = ui->imgDfrm->width();
    int height = ui->imgDfrm->height();

    imgBtnWidget = new QWidget(ui->imgDfrm);
    imgBtnWidget->resize(width,height);
    imgBtnLayout = new QHBoxLayout(imgBtnWidget);
    imgBtnLayout->setSpacing(6);  // 部件之间的间距
    imgBtnLayout->setContentsMargins(10, 0, 0, 0);  //  设置左侧、顶部、右侧和底部边距，
    imgBtnLayout->setAlignment(Qt::AlignLeft);
    imgBtnLayout->insertSpacing(0, -12);
    imgBtnLayout->addSpacing(10);

    searchLine = new DLineEdit();
    searchLine->setPlaceholderText("请输入镜像名");
    imgBtnLayout->addWidget(searchLine);

    searchBtn = new QPushButton("搜索");
    searchBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; height: 35px; width: 90px; font-size:15px;");
    imgBtnLayout->addWidget(searchBtn);

    deleteBtn = new DPushButton("删除镜像");
    deleteBtn->setStyleSheet("color: #FFFFFF; background-color: #F56C6C; border-radius: 5; border: 0px; height: 35px; width: 90px; font-size:15px;");
    imgBtnLayout->addWidget(deleteBtn);

    refreshBtn = new DPushButton("刷新");
    refreshBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; height: 35px; width: 90px; font-size:15px;");
    imgBtnLayout->addWidget(refreshBtn);

    pullImageBtn = new DPushButton("拉取镜像");
    pullImageBtn->setStyleSheet("color: #FFFFFF; background-color: #1E90FF; border-radius: 5; border: 0px; height: 35px; width: 90px; font-size:15px;");
    imgBtnLayout->addWidget(pullImageBtn);

    imgBtnLayout->addSpacing(10);

    columnWidget = new QWidget(ui->columnDfrm);
    columnLayout = new QHBoxLayout(columnWidget);
    columnLayout->setContentsMargins(15, 0, 0, 0);  //  设置左侧、顶部、右侧和底部边距，
    columnLayout->setSpacing(0);  // 部件之间的间距

    checkAllBtn = new QRadioButton(columnWidget);
    checkAllBtn->setFixedSize(height-20,height);
    columnLayout->addWidget(checkAllBtn);

    idLab = new DLabel("ID");
    idLab->setAlignment(Qt::AlignCenter);
    idLab->setFixedWidth(110);
    columnLayout->addWidget(idLab);

    tagsLab = new DLabel("标签");
    tagsLab->setAlignment(Qt::AlignCenter);
    tagsLab->setFixedWidth(110);
    columnLayout->addWidget(tagsLab);

    imageSizeLab = new DLabel("镜像尺寸");
    imageSizeLab->setAlignment(Qt::AlignCenter);
    imageSizeLab->setFixedWidth(110);
    columnLayout->addWidget(imageSizeLab);

    createTimeLab = new DLabel("创建时间");
    createTimeLab->setAlignment(Qt::AlignCenter);
    createTimeLab->setFixedWidth(110);
    columnLayout->addWidget(createTimeLab);

    operationLab = new DLabel("操作");
    operationLab->setAlignment(Qt::AlignCenter);
    operationLab->setFixedWidth(110);
    columnLayout->addWidget(operationLab);

    /*
     * 从sessionbus初始化镜像列表
    */
//    GetImageListFromJson();
}

void Image::GetImageArrayFromSessionBus()
{
    //构造一个method_call消息，服务名称为：com.bluesky.docker.Image，对象路径为：/com/bluesky/docker/Image
    //接口名称为com.bluesky.docker.Image，method名称为GetImageList
    QDBusMessage message = QDBusMessage::createMethodCall("com.bluesky.docker.Image",
                           "/com/bluesky/docker/Image",
                           "com.bluesky.docker.Image",
                           "GetImageList");
    //发送消息
    QDBusMessage response = QDBusConnection::sessionBus().call(message);
    //判断method是否被正确返回
    if (response.type() == QDBusMessage::ReplyMessage)
    {
        //从返回参数获取返回值
        imageArray = response.arguments().takeFirst().toString().toUtf8();

    }
    else
    {
        qDebug() << "容器数据获取失败";
    }
}

void Image::GetImageListFromJson()
{

}

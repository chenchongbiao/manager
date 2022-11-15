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

#include "image.h"
#include "ui_image.h"

#define B  1
#define KB 1000
#define MB 1000 * 1000
#define GB 1000 * 1000 * 1000
#define TB 1000 * 1000 * 1000 * 1000
#define EB 1000 * 1000 * 1000 * 1000 * 1000

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
    searchBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; height: 35px; width: 60px; font-size:15px;");
    imgBtnLayout->addWidget(searchBtn);

    deleteBtn = new DPushButton("删除镜像");
    deleteBtn->setStyleSheet("color: #FFFFFF; background-color: #F56C6C; border-radius: 5; border: 0px; height: 35px; width: 80px; font-size:15px;");
    imgBtnLayout->addWidget(deleteBtn);

    refreshBtn = new DPushButton("刷新");
    refreshBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; height: 35px; width: 80px; font-size:15px;");
    imgBtnLayout->addWidget(refreshBtn);

    pullImageBtn = new DPushButton("拉取镜像");
    pullImageBtn->setStyleSheet("color: #FFFFFF; background-color: #1E90FF; border-radius: 5; border: 0px; height: 35px; width: 80px; font-size:15px;");
    imgBtnLayout->addWidget(pullImageBtn);

    imgBtnLayout->addSpacing(10);

    columnWidget = new QWidget(ui->columnDfrm);
    columnLayout = new QHBoxLayout(columnWidget);
    columnLayout->setContentsMargins(15, 0, 0, 0);  //  设置左侧、顶部、右侧和底部边距，
    columnLayout->setSpacing(0);  // 部件之间的间距

    checkAllBtn = new QRadioButton(columnWidget);
    checkAllBtn->setFixedSize(height-20,height);
    connect(checkAllBtn,&QRadioButton::clicked,this,[=](){
        if (checkAllBtn->isChecked())
        {
            qDebug() << "全选按钮被点击";
            for(int i=0;i < ui->ListWdg->count();i++)
            {
                QWidget *curContaier = ui->ListWdg->itemWidget(ui->ListWdg->item(i));
                QRadioButton *radio = curContaier->findChildren<QRadioButton*>().at(0);
                if (checkRadioBtnList.indexOf(radio) == -1)  // 等于-1表示没被选中
                {
                    radio->setChecked(true);
                    checkRadioBtnList.append(radio);
                }
            }
        } else {
            qDebug() << "全选按钮取消";
            for(QRadioButton *radio: checkRadioBtnList)
            {
                radio->setChecked(false);
            }
            checkRadioBtnList.clear();
        }
    });
    columnLayout->addWidget(checkAllBtn);

    idLab = new DLabel("ID");
    idLab->setAlignment(Qt::AlignCenter);
    idLab->setFixedWidth(130);
    columnLayout->addWidget(idLab);

    tagsLab = new DLabel("标签");
    tagsLab->setAlignment(Qt::AlignCenter);
    tagsLab->setFixedWidth(150);
    columnLayout->addWidget(tagsLab);

    imageSizeLab = new DLabel("镜像尺寸");
    imageSizeLab->setAlignment(Qt::AlignCenter);
    imageSizeLab->setFixedWidth(90);
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
    GetImageListFromJson();
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
    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(imageArray,&jsonError);   // 转化为 JSON 文档
    if (!document.isNull() && (jsonError.error == QJsonParseError::NoError)) { // 解析未发生错误
        if (document.isArray()) { // JSON 文档为数组
            QJsonArray imageArray = document.array();
            int imgSize = imageArray.size();
            for(int i=0;i < imgSize;i++) {
                QJsonValue value = imageArray.at(i);
                QJsonObject obj = value.toObject();

                QWidget *imgWidget = new QWidget(ui->ListWdg);  // 主页软件单条数据的widget
                imgWidget->resize(ui->ListWdg->width(),ui->ListWdg->height());

                QHBoxLayout *layout = new QHBoxLayout(imgWidget);
                layout->setContentsMargins(0, 0, 0, 0);  //  设置左侧、顶部、右侧和底部边距，

                QRadioButton *checkBtn = new QRadioButton(ui->ListWdg);
                checkBtn->setFixedSize(ui->imgDfrm->height()-20,ui->imgDfrm->height());
                layout->addWidget(checkBtn);
                connect(checkBtn,&QRadioButton::clicked, this, [=](){
                    QRadioButton *curBtn = (QRadioButton *) sender();// 槽函数中调用sender函数，返回指向发送信号的对象的指针
                    int index = checkRadioBtnList.indexOf(curBtn);
                    if (index == -1) // 等于-1代表没有被选中了，添加到QList中
                    {
                        qDebug() << "当前选中" << curBtn->parent()->findChildren<DLabel *>().at(0)->text();
                        checkRadioBtnList.append(curBtn);
                    } else {
                        qDebug() << "当前取消" << curBtn->parent()->findChildren<DLabel *>().at(0)->text();
                        checkRadioBtnList.removeAt(index);
                    }
                    if (checkRadioBtnList.count() == ui->ListWdg->count() && !checkAllBtn->isChecked()) // 所有数据都被选中 并且全选按钮未被选中
                    {
                        checkAllBtn->setChecked(true);
                    } else if (checkRadioBtnList.count() != ui->ListWdg->count() && checkAllBtn->isChecked()){ // 所有数据未被选中 但是全选按钮被选中
                        checkAllBtn->setChecked(false);
                    }
                });

                QString id = obj.value("Id").toString().mid(7,12);
                DLabel *imgId = new DLabel(id);
                imgId->setAlignment(Qt::AlignCenter);
                imgId->setFixedWidth(130);
                layout->addWidget(imgId);

                QString RepoTags = obj.value("RepoTags").toArray().at(0).toString();
                DLabel *tags = new DLabel(RepoTags);
                tags->setFixedWidth(150);
                layout->addWidget(tags);

                qint64 size = obj.value("Size").toInt();
                DLabel *imgSize = new DLabel(QString("%1").arg(formatImageSize(size)));
                imgSize->setFixedWidth(90);
                layout->addWidget(imgSize);

                qint64 createTime = obj.value("Created").toInt();
                QString dateTime = QDateTime::fromSecsSinceEpoch(createTime).toString("yyyy-MM-dd hh:mm:ss.zzz");
                DLabel *dockerName = new DLabel(dateTime);
                dockerName->setFixedWidth(110);
                layout->addWidget(dockerName);

                DLabel *operation = new DLabel();
                operation->setAlignment(Qt::AlignCenter);
                operation->setFixedWidth(150);

                QWidget *operationWidget = new QWidget(operation);
                operationWidget->resize(operationWidget->width(),operationWidget->height());
                QHBoxLayout *operationLayout = new QHBoxLayout(operationWidget);
                operationLayout->setContentsMargins(10, 10, 0, 0);  //  设置左侧、顶部、右侧和底部边距，
                DPushButton *infoBtn = new DPushButton("信息");
                infoBtn->setFixedSize(40,20);
                infoBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; height: 40px; font-size:13px;");
                operationLayout->addWidget(infoBtn);

                DPushButton *delBtn = new DPushButton("删除");
                delBtn->setFixedSize(40,20);
                delBtn->setStyleSheet("color: #FFFFFF; background-color: #F56C6C; border-radius: 5; border: 0px; height: 40px; font-size:13px;");
                operationLayout->addWidget(delBtn);
                layout->addWidget(operation);


                QListWidgetItem *containerItem=new QListWidgetItem(ui->ListWdg);
                containerItem->setSizeHint(QSize(40,40));
                //  containerItem->setToolTip(); // 提示框
                //  containerItem->setFlags(Qt::ItemIsSelectable); // 取消选择项
                ui->ListWdg->setItemWidget(containerItem,imgWidget);  // 将dockerWidgetr赋予containerItem

            }
        }
    }
}


QString Image::formatImageSize(qint64 imgSize) {
    if (imgSize < KB) {
        return QString("%1KB").arg(QString::number(double(imgSize)/double(KB),'f',2));
    } else if (imgSize < MB) {
        return QString("%1KB").arg(QString::number(double(imgSize)/double(KB),'f',2));
    } else if (imgSize < GB) {
        return QString("%1MB").arg(QString::number(double(imgSize)/double(MB),'f',2));
    } else if (imgSize < TB) {
        return QString("%1GB").arg(QString::number(double(imgSize)/double(GB),'f',2));
    } /*else if (imgSize < EB) {
        return QString("%1TB").arg(QString::number(double(imgSize)/double(TB),'f',2));
    } else {
        return QString("%1EB").arg(QString::number(double(imgSize)/double(EB),'f',2));
    }*/
}

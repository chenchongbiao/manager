#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include <DLabel>
//#include <QRadioButton>

#include "createcontainerdialog.h"
#include "ui_createcontainerdialog.h"
#include "dbusclient.h"
#include "Utils/utils.h"

CreateContainerDialog::CreateContainerDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateContainerDialog)
{
    ui->setupUi(this);
    initUI();
}

CreateContainerDialog::~CreateContainerDialog()
{
    delete ui;
}

void CreateContainerDialog::initUI()
{
    initLeftMenuUI();
    initCheckImgUI();
}

void CreateContainerDialog::initLeftMenuUI()
{
    leftMenuWdg = new QWidget(ui->leftBtnFrm);
    leftMenuWdgLayout = new QVBoxLayout(leftMenuWdg);
    leftMenuWdgLayout->setSpacing(6);  //设置间距
    leftMenuWdgLayout->setContentsMargins(0, 0, 0, 0); //  设置左侧、顶部、右侧和底部边距

    checkImgBtn = new DPushButton("选择镜像");
    checkImgBtn->setFixedSize(ui->leftBtnFrm->width(),btnHeight);
    connect(checkImgBtn,&DPushButton::clicked,this,[=](){chooseLeftMenu(0);});
    leftMenuWdgLayout->addWidget(checkImgBtn);

    containerInfoBtn = new DPushButton("容器信息");
    containerInfoBtn->setFixedSize(ui->leftBtnFrm->width(),btnHeight);
    leftMenuWdgLayout->addWidget(containerInfoBtn);

    portMappingBtn = new DPushButton("端口映射");
    portMappingBtn->setFixedSize(ui->leftBtnFrm->width(),btnHeight);
    leftMenuWdgLayout->addWidget(portMappingBtn);

    volumeMountBtn = new DPushButton("存储挂载");
    volumeMountBtn->setFixedSize(ui->leftBtnFrm->width(),btnHeight);
    leftMenuWdgLayout->addWidget(volumeMountBtn);

    leftBtnList << checkImgBtn
                << containerInfoBtn
                << portMappingBtn
                << volumeMountBtn;

    for(int i=0;i < leftBtnList.count();i++) {
        DPushButton *btn = leftBtnList.at(i);
        checkMenu(btn,false);

        connect(btn,&DPushButton::clicked,this,[=](){
           DPushButton *curBtn = (DPushButton *) sender();
           qDebug() << "当前按下" << curBtn->text();
           for(int i=0;i < leftBtnList.count();i++) {
               DPushButton *btn = leftBtnList.at(i);
               checkMenu(btn,curBtn==btn);
           }
        });
    }

    checkMenu(checkImgBtn,true);  // 默认选中选择镜像按钮
}

void CreateContainerDialog::initCheckImgUI()
{
    searchWdg = new QWidget(ui->searchDfrm);
    searchWdgLayout = new QHBoxLayout(searchWdg);
    searchWdgLayout->setSpacing(6);            // 设置控件间距
    searchWdgLayout->setContentsMargins(6, 0, 0, 0); //  设置左侧、顶部、右侧和底部边距

    searchEdit = new DLineEdit();
    searchEdit->setFixedSize(searchEditWidth,45);
    searchEdit->setStyleSheet("background-color: #FFFFFF; border-radius: 5; border: 1px solid #E6E6E6; font-size:15px;");
    searchWdgLayout->addWidget(searchEdit);

    searchBtn = new DPushButton("搜索");
    searchBtn->setFixedSize(searchBtnWidth,ui->searchDfrm->height()-15);
    searchBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; font-size:15px;");
    connect(searchBtn,&DPushButton::clicked,this,&CreateContainerDialog::SearchImage);
    searchWdgLayout->addWidget(searchBtn);

    columnWidget = new QWidget(ui->columnDfrm);
    columnWidget->resize(ui->columnDfrm->width(),ui->columnDfrm->height());
    columnLayout = new QHBoxLayout(columnWidget);
    columnLayout->setContentsMargins(0, 0, 0, 0);  //  设置左侧、顶部、右侧和底部边距，
    columnLayout->setSpacing(0);  // 部件之间的间距

    idLab = new DLabel("ID");
    idLab->setAlignment(Qt::AlignCenter);
    idLab->setFixedSize(100,ui->columnDfrm->height());
    columnLayout->addWidget(idLab);

    tagsLab = new DLabel("标签");
    tagsLab->setAlignment(Qt::AlignCenter);
    tagsLab->setFixedSize(200,ui->columnDfrm->height());
    columnLayout->addWidget(tagsLab);

    imageSizeLab = new DLabel("镜像尺寸");
    imageSizeLab->setAlignment(Qt::AlignCenter);
    imageSizeLab->setFixedSize(80,ui->columnDfrm->height());
    columnLayout->addWidget(imageSizeLab);

    createTimeLab = new DLabel("创建时间");
    createTimeLab->setAlignment(Qt::AlignCenter);
    createTimeLab->setFixedSize(110,ui->columnDfrm->height());
    columnLayout->addWidget(createTimeLab);

    imageArray = DBusClient::GetImageList();
    initImageListUI();

}

void CreateContainerDialog::initImageListUI()
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

//                QRadioButton *checkBtn = new QRadioButton(ui->ListWdg);
//                checkBtn->setFixedSize(ui->imgDfrm->height()-20,ui->imgDfrm->height());
//                layout->addWidget(checkBtn);
                QString id = obj.value("Id").toString().mid(7,12);
                DLabel *imgId = new DLabel(id);
                imgId->setAlignment(Qt::AlignCenter);
                imgId->setFixedWidth(110);
                layout->addWidget(imgId);

                QString RepoTags = obj.value("RepoTags").toArray().at(0).toString();
                DLabel *tags = new DLabel(RepoTags);
                tags->setFixedWidth(200);
                layout->addWidget(tags);

                qint64 size = obj.value("Size").toInt();
                DLabel *imgSize = new DLabel(QString("%1").arg(Utils::formatSize(size)));
                imgSize->setFixedWidth(80);
                layout->addWidget(imgSize);

                qint64 createTime = obj.value("Created").toInt();
                QString dateTime = QDateTime::fromSecsSinceEpoch(createTime).toString("yyyy-MM-dd hh:mm:ss");
                DLabel *dockerName = new DLabel(dateTime);
                dockerName->setFixedWidth(110);
                layout->addWidget(dockerName);

                QListWidgetItem *containerItem=new QListWidgetItem(ui->ListWdg);
                containerItem->setSizeHint(QSize(40,40));
                //  containerItem->setToolTip(); // 提示框
                //  containerItem->setFlags(Qt::ItemIsSelectable); // 取消选择项
                ui->ListWdg->setItemWidget(containerItem,imgWidget);  // 将dockerWidgetr赋予containerItem

            }
        }
    }
}

void CreateContainerDialog::SearchImage()
{
    qDebug() << "搜索镜像按钮被点击";
    QString keyword = searchEdit->text();
    qDebug() << "镜像名" << keyword;
    imageArray = DBusClient::SearchImageByName(keyword);
    if (imageArray.isEmpty()) {
        qDebug() << "镜像数据为空";
        imageArray = DBusClient::GetImageList();
    }
    ui->ListWdg->clear();    // 清除控件
    initImageListUI();       // 重新获取镜像数据
}

void CreateContainerDialog::checkMenu(QPushButton *btn,bool isCheck)
{
    if (isCheck)
    {
        btn->setStyleSheet("color: #409EFF; border-radius: 5; border: 1px solid rgb(64,158,255); font-size:15px;");
    } else {
        btn->setStyleSheet("color: #252525; border-radius: 5; border: 0px;");
    }
}

void CreateContainerDialog::chooseLeftMenu(int index)  // 菜单切换逻辑
{
    nowMenu = index;
    ui->stackedWidget->setCurrentIndex(nowMenu);
}


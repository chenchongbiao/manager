#include "createcontainerdialog.h"
#include "ui_createcontainerdialog.h"

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
    searchWdgLayout->addWidget(searchBtn);

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

#include <QGraphicsOpacityEffect>
#include <QtConcurrent>
#include <QTimer>
#include <QProcess>
#include <sstream>
#include <math.h>
#include <unistd.h>

#include "homepagestatus.h"
#include "ui_homepagestatus.h"
#include "waterprogress.h"
#include "Utils/utils.h"

#define MB (1024 * 1024)
#define KB (1024)

HomePageStatus::HomePageStatus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomePageStatus)
{
    ui->setupUi(this);
    initUI();

    QTimer *timer = new QTimer(this);
    timer->start(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateWaterProgress()));

    connect(loadStatusWp->getTimer(), SIGNAL(timeout()), this, SLOT(computerLoad()));  // 计算负载均衡状态
    connect(cpuStatusWp->getTimer(), SIGNAL(timeout()), this, SLOT(getCPU()));
    connect(memStatusWp->getTimer(), SIGNAL(timeout()), this, SLOT(getMemory()));
    connect(diskStatusWp->getTimer(), SIGNAL(timeout()), this, SLOT(getDisk()));

    process = new QProcess(this);
    connect(process, SIGNAL(readyRead()), this, SLOT(ReadData()));
}

HomePageStatus::~HomePageStatus()
{
    delete ui;
}

void HomePageStatus::initUI()
{
    // 初始化分界线
    ui->line1_widget->setStyleSheet("background-color:#808080");
    QGraphicsOpacityEffect *opacityEffect_1 = new QGraphicsOpacityEffect;
    opacityEffect_1->setOpacity(0.1);
    ui->line1_widget->setGraphicsEffect(opacityEffect_1);

    cpuNum = Utils::exec("cpufreq-info | grep 'analyzing CPU'").split("\n").size();  // CPU个数固定，不重复计算)
    ui->cpu_core_num->setText(QString("%1核心").arg(cpuNum));
    loadStatusWp = new WaterProgress(ui->load_status,900);
    cpuStatusWp = new WaterProgress(ui->cpu_status,900);
    memStatusWp = new WaterProgress(ui->memory_status,300);
    diskStatusWp = new WaterProgress(ui->disk_status,1000);
    updateWaterProgress();
}

void HomePageStatus::updateWaterProgress()
{
    loadStatusWp->setValue(loadPercent);  // 修改负载状态
    ui->load_status_info->setText(loadMsg);
    cpuStatusWp->setValue(cpuPercent);  // 修改CPU状态
    memStatusWp->setValue(memoryPercent);  // 修改内存状态
    ui->memory_space->setText(memoryMsg);
    diskStatusWp->setValue(diskPercent);  // 修改硬盘状态
    ui->disk_space->setText(diskyMsg);
}

void HomePageStatus::getCPU()
{
    if (process->state() == QProcess::NotRunning) {
        totalNew = idleNew = 0;
        process->start(QString("cat %1").arg(cpuFile));
    }
}

void HomePageStatus::getMemory()
{
    if (process->state() == QProcess::NotRunning) {
        process->start(QString("cat %1").arg(memFile));
    }
}

void HomePageStatus::getDisk()
{
    if (process->state() == QProcess::NotRunning) {
        process->start("df -h");
    }
}

void HomePageStatus::computerLoad()
{
    load = Utils::exec("uptime" + Utils::awk("average: ","2") + Utils::awk(",","1")).toFloat();  // 获取负载均衡数据
    // 算法来自宝塔，因为水球的数值为整形，最后做了转换
    loadPercent = (int)round(load / (cpuNum * 2) * 100);
    if (loadPercent > 100)
    {
        loadPercent = 100;
    }
    if (loadPercent <= 30)
    {
        loadMsg = "运行流畅";
    }
    if (loadPercent > 30 && loadPercent <= 70)
    {
        loadMsg = "运行正常";
    }
    if (loadPercent > 70 && loadPercent <= 90)
    {
        loadMsg = "运行缓慢";
    }
    if (loadPercent > 90)
    {
        loadMsg = "运行堵塞";
    }
}

void HomePageStatus::ReadData()
{
    QtConcurrent::run([=](){
        while (!process->atEnd()) {
            QString s = QLatin1String(process->readLine());
            if (s.startsWith("cpu")) {
                QStringList list = s.split(" ");
                idleNew = list.at(5).toInt();
                foreach (QString value, list) {
                    totalNew += value.toInt();
                }
                int total = totalNew - totalOld;
                int idle = idleNew - idleOld;
                cpuPercent = 100 * (total - idle) / total;
                totalOld = totalNew;
                idleOld = idleNew;
                break;
            } else if (s.startsWith("MemTotal")) {
                s = s.replace(" ", "");
                s = s.split(":").at(1);
                memoryAll = s.left(s.length() - 3).toInt() / KB;
            } else if (s.startsWith("MemFree")) {
                s = s.replace(" ", "");
                s = s.split(":").at(1);
                memoryFree = s.left(s.length() - 3).toInt() / KB;
    //            qDebug() << "MemFree " << memoryFree << endl;
            } else if (s.startsWith("Buffers")) {
                s = s.replace(" ", "");
                s = s.split(":").at(1);
                memoryFree += s.left(s.length() - 3).toInt() / KB;
    //            qDebug() << "Buffers " << memoryFree << endl;
            } else if (s.startsWith("Cached")) {
                s = s.replace(" ", "");
                s = s.split(":").at(1);
                memoryFree += s.left(s.length() - 3).toInt() / KB;
                memoryUse = memoryAll - memoryFree;
                memoryPercent = 100 * memoryUse / memoryAll;
                memoryMsg = QString("%1MB/%2MB").arg(memoryUse).arg(memoryAll);
//                qDebug() << s;
                break;
            } else if (s.startsWith("/dev/sda") | s.startsWith("/dev/nvme")) {
                s = s.replace(QRegExp("[\\s]+"), " ");
                QStringList list = s.split(" ");
                diskUse = list.at(2).left(list.at(2).length() - 1).toInt();
                diskAll = list.at(1).left(list.at(1).length() - 1).toInt();
                diskPercent = list.at(4).left(list.at(4).length() - 1).toInt();
                diskyMsg = QString("%1/%2").arg(list.at(2)).arg(list.at(1));
//                qDebug() << QString("diskUse %1 diskAll %2 diskPercent %3").arg(diskUse).arg(diskAll).arg(diskPercent);
                break;
            }
        }
    });
}

#include <DLabel>

#include "systeminfo.h"
#include "utils.h"

SystemInfo::SystemInfo(QWidget *parent) :
    DLabel(parent)
{
    getSystemInfo();  // 获取系统信息，发行版 IP地址 架构等
    this->resize(740,45);
    this->setText(QString("  系统：%1 %2  网络：%3").arg(issue).arg(architecture).arg(ip));
}

SystemInfo::~SystemInfo()
{

}

void SystemInfo::getSystemInfo()
{
    issue = Utils::exec(QString("cat %1").arg(issueFile)).remove(" \\n").remove("\\l");  // 发行版
    ip = Utils::exec("hostname -I").split(" ").at(0);
    architecture = Utils::exec("uname -m");
}


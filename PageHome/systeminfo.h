#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

#include <QWidget>
#include <DLabel>

DWIDGET_USE_NAMESPACE

class SystemInfo : public DLabel
{
    Q_OBJECT

public:
    explicit SystemInfo(QWidget *parent = nullptr);
    ~SystemInfo();
private:
    void getSystemInfo();

private:
    QString issue;  // 发行版
    QString ip;     // ip地址
    QString architecture;  // 架构
    QString issueFile="/etc/issue";
};

#endif // SYSTEMINFO_H

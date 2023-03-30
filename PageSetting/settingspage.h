#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFormLayout>

#include "common/multiselectlist.h"

class SettingsPage : public DFrame
{
    Q_OBJECT
public:
    explicit SettingsPage(QWidget *parent = nullptr);

signals:

public slots:

private:
    void initUI();

private:
    QFormLayout *mainLayout;          // 主要布局
    QSqlDatabase *sqliteDB;           // sqlite的数据库连接
    QSqlQuery *query;                 // 执行语句
};

#endif // SETTINGSPAGE_H

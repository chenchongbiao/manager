#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <QWidget>
#include <DPushButton>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "common/multiselectlist.h"

DWIDGET_USE_NAMESPACE

class WareHouse : public QWidget
{
    Q_OBJECT
public:
    explicit WareHouse(QWidget *parent = nullptr);

signals:

public slots:

private:
    void initUI();

private:
    MultiSelectList *multiSelectList;
    DPushButton *addBtn;
    DPushButton *delBtn;

    QSqlDatabase *sqliteDB;           // sqlite的数据库连接
    QSqlQuery *query;                 // 执行语句
};

#endif // WAREHOUSE_H

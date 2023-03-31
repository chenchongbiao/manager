#ifndef SOFTPAGE_H
#define SOFTPAGE_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "common/multiselectlist.h"

DWIDGET_USE_NAMESPACE

class SoftPage : public QWidget
{
    Q_OBJECT
public:
    explicit SoftPage(QWidget *parent = nullptr);

signals:

public slots:

private:
    void initUI();

private:
    MultiSelectList *multiSelectList;

    DLineEdit *lineEdit;
    DPushButton *searchBtn;

    QSqlDatabase *sqliteDB;           // sqlite的数据库连接
    QSqlQuery *query;                 // 执行语句
};

#endif // SOFTPAGE_H

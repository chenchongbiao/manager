#ifndef ENVPAGE_H
#define ENVPAGE_H

#include <QWidget>
#include <DLineEdit>
#include <DPushButton>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "common/multiselectlist.h"

DWIDGET_USE_NAMESPACE

class EnvPage : public QWidget
{
    Q_OBJECT
public:
    explicit EnvPage(QWidget *parent = nullptr);

signals:

public slots:

private:
    void initUI();

private slots:
    void addDialog();  // 添加环境的对话框

private:
    MultiSelectList *multiSelectList;
    DLineEdit *lineEdit;
    DPushButton *searchBtn;
    DPushButton *addBtn;
    DPushButton *delBtn;

    QSqlDatabase *sqliteDB;           // sqlite的数据库连接
    QSqlQuery *query;                 // 执行语句
};

#endif // ENVPAGE_H

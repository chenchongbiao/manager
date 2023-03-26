#ifndef MONGODB_H
#define MONGODB_H

#include <QWidget>
#include <DLineEdit>
#include <DPushButton>
#include <DFrame>

#include "common/multiselectlist.h"

DWIDGET_USE_NAMESPACE

class Mongodb : public QWidget
{
    Q_OBJECT
public:
    explicit Mongodb(QWidget *parent = nullptr);

signals:

public slots:

private:
    void initUI();
    void addDBDialog();

private:
    MultiSelectList *list;

    DLineEdit *lineEdit;
    DPushButton *searchBtn;
    DPushButton *addBtn;
    DPushButton *delBtn;
};

#endif // MONGODB_H

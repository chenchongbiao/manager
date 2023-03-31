#ifndef REDIS_H
#define REDIS_H

#include <QWidget>
#include <DLineEdit>
#include <DPushButton>
#include <DFrame>

#include "common/multiselectlist.h"

DWIDGET_USE_NAMESPACE

class Redis : public QWidget
{
    Q_OBJECT
public:
    explicit Redis(QWidget *parent = nullptr);

signals:

public slots:

private:
    void initUI();

private:
    MultiSelectList *list;

    DLineEdit *lineEdit;
    DPushButton *searchBtn;
    DPushButton *addBtn;
    DPushButton *delBtn;
};

#endif // REDIS_H

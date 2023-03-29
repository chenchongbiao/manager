#ifndef SOFTPAGE_H
#define SOFTPAGE_H

#include <QWidget>

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
};

#endif // SOFTPAGE_H

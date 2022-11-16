#ifndef CONTAINERINFODIALOG_H
#define CONTAINERINFODIALOG_H

#include <QWidget>

namespace Ui {
class ContainerInfoDialog;
}

class ContainerInfoDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ContainerInfoDialog(QWidget *parent = nullptr);
    ~ContainerInfoDialog();

private:
    void initUI();

private:
    Ui::ContainerInfoDialog *ui;
};

#endif // CONTAINERINFODIALOG_H

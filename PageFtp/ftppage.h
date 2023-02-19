#ifndef FTPPAGE_H
#define FTPPAGE_H

#include <QWidget>

#include "PageDocker/mlistwidget.h"

namespace Ui {
class FtpPage;
}

class FtpPage : public QWidget
{
    Q_OBJECT

public:
    explicit FtpPage(QWidget *parent = nullptr);
    ~FtpPage();

private:
    Ui::FtpPage *ui;
};

#endif // FTPPAGE_H

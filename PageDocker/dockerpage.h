#ifndef DOCKERPAGE_H
#define DOCKERPAGE_H

#include <DToolBar>
#include <QWidget>

DWIDGET_USE_NAMESPACE

namespace Ui {
class DockerPage;
}

class DockerPage : public QWidget
{
    Q_OBJECT

public:
    explicit DockerPage(QWidget *parent = nullptr);
    ~DockerPage();
private:
    void initUI();
private:
    Ui::DockerPage *ui;
    DToolBar *pToolBar;
};

#endif // DOCKERPAGE_H

#include <QSqlQuery>

#include "model/containermodel.h"

#ifndef CONTAINERMAPPER_H
#define CONTAINERMAPPER_H


class ContainerMapper
{
public:
    ContainerMapper();
    bool Insert(ContainerModel containerModel);  // 插入数据
    QSqlQuery GetContainerList();  // 获取容器列表数据
};

#endif // CONTAINERMAPPER_H

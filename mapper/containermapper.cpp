#include <QSqlQuery>

#include "model/containermodel.h"
#include "containermapper.h"

ContainerMapper::ContainerMapper()
{

}

bool ContainerMapper::Insert(ContainerModel containerModel)
{
    QSqlQuery query;
    bool result = query.exec(QString(R"(INSERT INTO container (container_id,name,image,state,port,command) values(%1,%2,%3,%4,%5,%6);)")
               .arg(containerModel.GetContainerId())
               .arg(containerModel.GetName())
               .arg(containerModel.GetImage())
               .arg(containerModel.GetState())
               .arg(containerModel.GetPort())
               .arg((containerModel.GetCommand())));
    return result;
}

QSqlQuery ContainerMapper::GetContainerList()
{
    QSqlQuery query;
    query.exec(QString(R"(SELECT container_id,name,state,image,port FROM container;)"));
    return query;
}

#include "containermodel.h"

ContainerModel::ContainerModel()
{

}

ContainerModel::ContainerModel(QString ContainerId,QString Name,QString State,QString Image,QString Port,QString Command)
{
    this->ContainerId = ContainerId;
    this->Name = Name;
    this->State = State;
    this->Image = Image;
    this->Port = Port;
    this->Command = Command;
}

QString ContainerModel::GetContainerId()
{
    return this->ContainerId;
}

void ContainerModel::SetContainerId(QString ContainerId)
{
    this->ContainerId = ContainerId;
}

QString ContainerModel::GetName()
{
    return this->Name;
}

void ContainerModel::SetName(QString Name)
{
    this->Name = Name;
}

QString ContainerModel::GetState()
{
    return this->State;
}

void ContainerModel::SetState(QString State)
{
    this->State = State;
}

QString ContainerModel::GetImage()
{
    return this->Image;
}

void ContainerModel::SetImage(QString Image)
{
    this->Image = Image;
}

QString ContainerModel::GetPort()
{
    return this->Port;
}

void ContainerModel::SetPort(QString Port)
{
    this->Port = Port;
}

QString ContainerModel::GetCommand()
{
    return this->Command;
}

void ContainerModel::SetCommand(QString Command)
{
    this->Command = Command;
}

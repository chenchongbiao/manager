#-------------------------------------------------
#
# Project created by QtCreator 2022-10-17T15:33:15
#
#-------------------------------------------------

QT       += core gui concurrent sql dbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = manager
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
CONFIG += link_pkgconfig
PKGCONFIG += dtkwidget
SOURCES += \
    main.cpp \
    widget.cpp \
    Utils/utils.cpp \
    PageHome/homepagesoftitem.cpp \
    PageHome/waterprogress.cpp \
    PageHome/homepagestatus.cpp \
    PageHome/systeminfo.cpp \
    PageHome/leftmenu.cpp \
    PageDocker/dockerpage.cpp \
    PageDocker/dockerpagetopmenu.cpp \
    PageDocker/container.cpp \
    PageDocker/image.cpp \
    PageDocker/containerinfodialog.cpp \
    PageDocker/createcontainerdialog.cpp \
    PageDocker/dbusclient.cpp \
    PageDocker/network.cpp \
    PageDocker/mlistwidget.cpp \
    PageDocker/volume.cpp


HEADERS += \
    widget.h \
    Utils/utils.h \
    PageHome/homepagesoftitem.h \
    PageHome/waterprogress.h \
    PageHome/homepagestatus.h \
    PageHome/systeminfo.h \
    PageHome/leftmenu.h \
    PageDocker/dockerpage.h \
    PageDocker/dockerpagetopmenu.h \
    PageDocker/container.h \
    PageDocker/image.h \
    PageDocker/containerinfodialog.h \
    PageDocker/createcontainerdialog.h \
    PageDocker/dbusclient.h \
    PageDocker/network.h \
    PageDocker/mlistwidget.h \
    PageDocker/volume.h


RESOURCES +=         resources.qrc

FORMS += \
    widget.ui \
    PageHome/homepagesoftitem.ui \
    PageHome/homepagestatus.ui \
    PageDocker/dockerpage.ui \
    PageDocker/container.ui \
    PageDocker/image.ui \
    PageDocker/containerinfodialog.ui \
    PageDocker/createcontainerdialog.ui \
    PageDocker/network.ui \
    PageDocker/mlistwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

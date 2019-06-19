#-------------------------------------------------
#
# Project created by QtCreator 2019-06-08T15:39:58
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ttms
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

SOURCES += \
        main.cpp \
        login.cpp \
    register.cpp \
    dboper.cpp \
    mainmenu_root.cpp \
    mainmenu_manager.cpp \
    mainmenu_user.cpp \
    ticket.cpp

HEADERS += \
        login.h \
    dboper.h \
    register.h \
    mainmenu_root.h \
    mainmenu_manager.h \
    ../DBOP/Client.h \
    mainmenu_user.h \
    ticket.h

FORMS += \
        login.ui \
    register.ui \
    mainmenu_root.ui \
    mainmenu_manager.ui \
    mainmenu_user.ui \
    ticket.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc

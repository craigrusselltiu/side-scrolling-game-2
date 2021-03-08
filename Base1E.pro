#-------------------------------------------------
#
# Project created by QtCreator 2019-03-16T14:24:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Base1E
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


SOURCES += \
        main.cpp \
        dialog.cpp \
    config.cpp \
    player.cpp \
    position.cpp \
    worldobject.cpp \
    background.cpp \
    eyecandy.cpp \
    worldobjectfactory.cpp \
    worldmanager.cpp \
    obstacle.cpp \
    decorator.cpp \
    auradecorator.cpp \
    movedecorator.cpp

HEADERS += \
        dialog.h \
    config.h \
    player.h \
    position.h \
    worldobject.h \
    background.h \
    eyecandy.h \
    worldobjectfactory.h \
    worldmanager.h \
    define.h \
    obstacle.h \
    decorator.h \
    auradecorator.h \
    movedecorator.h

FORMS += \
        dialog.ui

COPIES += candy

candy.files += $$files(resources)
candy.path = $$OUT_PWD/debug

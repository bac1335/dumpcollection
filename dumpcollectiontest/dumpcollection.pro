#-------------------------------------------------
#
# Project created by QtCreator 2020-07-22T09:12:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dumpcollection
TEMPLATE = app

win32{
    CONFIG(debug,debug|release){
        LIBS += -L$$PWD/dumpcollection/debug/ -ldumpcollection
    }
    CONFIG(release,rebug|release){
        LIBS += -L$$PWD/dumpcollection/release/ -ldumpcollection
    }

}

include($$PWD/dumpcollection/dumpcollection.pri)

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
INCLUDEPATH += $$PWD/dumpcollection
DEFINES += USEREMOTELOG

SOURCES += \
        main.cpp \
        widget.cpp

HEADERS += \
        dumpcollection/LLSExceptionHandler.h \
        dumpcollection/dunmconfig.h \
        dumpcollection/llsrsmanager.h \
        dumpcollection/tllogger.h \
        widget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

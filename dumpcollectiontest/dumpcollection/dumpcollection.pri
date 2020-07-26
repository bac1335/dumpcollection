
QT += network

LIBS += -lDbgHelp

QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO

INCLUDEPATH += $$PWD/

DEFINES += USEREMOTELOG

HEADERS += \
    $$PWD/LLSExceptionHandler.h \
    $$PWD/dunmconfig.h \
    $$PWD/llsrsmanager.h \
    $$PWD/tllogger.h

SOURCES += \
    $$PWD/LLSExceptionHandler.cpp \
    $$PWD/llsrsmanager.cpp \
    $$PWD/tllogger.cpp

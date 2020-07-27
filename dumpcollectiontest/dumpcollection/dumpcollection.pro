
QT +=   gui network widgets
TARGET = dumpcollection
TEMPLATE = lib
LIBS += -ldbghelp

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
    LLSExceptionHandler.cpp \
    llsrsmanager.cpp \
    tllogger.cpp

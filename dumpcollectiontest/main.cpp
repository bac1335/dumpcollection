#include "widget.h"
#include <QApplication>
#include "LLSExceptionHandler.h"

#include <QStandardPaths>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LLSExceptionHandler::initExceptionHandler();

    LLSExceptionHandler::initLogHandler();

    LLSExceptionHandler::initRemoteTransmission();

    Widget w;
    w.show();

    return a.exec();
}

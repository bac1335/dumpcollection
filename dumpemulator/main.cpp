#include <QGuiApplication>
#include "emulatormanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    EmulatorManager manager;

    return app.exec();
}

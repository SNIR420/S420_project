#include "modbusserver.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ModbusServer server;
    if (!server.startServer(502))
        return -1;

    return a.exec();
}

#include <QCoreApplication>

#include "multithreadedtcpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QtWebServer::MultithreadedTcpServer s;
    s.listen(QHostAddress::Any, 3000);
    return a.exec();
}

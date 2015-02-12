#include <QCoreApplication>
#include <QFile>

#include "tcp/tcpmultithreadedserver.h"
#include "http/httpwebengine.h"
#include "http/httpiodeviceresource.h"

using namespace QtWebServer;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Tcp::MultithreadedServer s;
    Http::WebEngine w;

    w.addResource(new Http::IODeviceResource(
                      "/test",
                      new QFile("/home/jacob/text.html")));

    s.setResponder(&w);
    s.listen(QHostAddress::Any, 3000);
    return a.exec();
}

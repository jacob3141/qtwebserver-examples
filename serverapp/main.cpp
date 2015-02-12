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

    Http::IODeviceResource *r = new Http::IODeviceResource(
                "/test",
                new QFile("/home/jacob/text.html"));
    r->setContentType("text/html");
    w.addResource(r);

    s.setResponder(&w);
    s.listen(QHostAddress::Any, 3000);
    return a.exec();
}

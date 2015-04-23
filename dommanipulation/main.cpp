//
// Copyright 2010-2015 Jacob Dawid <jacob@omg-it.works>
//
// This file is part of QtWebServer.
//
// QtWebServer is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// QtWebServer is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public
// License along with QtWebServer.
// If not, see <http://www.gnu.org/licenses/>.
//
// It is possible to obtain a commercial license of QtWebServer.
// Please contact Jacob Dawid <jacob@omg-it.works>
//

// Qt includes
#include <QCoreApplication>
#include <QDomText>

// QtWebServer includes
#include "tcp/tcpmultithreadedserver.h"
#include "http/httpwebengine.h"
#include "http/httpresource.h"
#include "html/htmldocument.h"

using namespace QtWebServer;

// Usually, this should go into its own files, of course.
class Resource : public Http::Resource {
public:
    Resource() : Http::Resource("/") { }
    ~Resource() { }

    void deliver(const Http::Request&, Http::Response& response) {
        // In a real world application, one would interpret the request
        // and deliver a proper response.
        response.setStatusCode(Http::Ok);

        // Create a new HTML document
        Html::Document document;

        // Set the title
        document.setTitle("A QtWebServer example");

        // Create a new ul-element.
        QDomElement unorderedList = document.createElement("ul");

        // Build a simple unordered list.
        for(int i = 0; i < 42; i++) {
            // Assign each odd number the class "odd-number".
            document.appendHtml(unorderedList,
                QString("<li class=\"%1\">%2</li>")
                    .arg(i % 2 == 1 ? "odd-number" : "")
                    .arg(i));
        }

        // Append the unordered list element to the documents body element.
        document.body().appendChild(unorderedList);

        // Now let's manipulate the DOM.
        // Query all li elements carrying the class "odd-number"
        QList<QDomElement> oddNumberLiElements
            = document.elementsByClass("odd-number");

        // Iterate over them.
        foreach(QDomElement element, oddNumberLiElements) {
            // Get the underlying DOM text fragment.
            QDomText domText = element.firstChild().toText();

            // Manipulate it. As domText is directly referring to the DOM
            // text fragment, the change takes effect immediately.
            domText.setData(QString("%1").arg(domText.data().toInt() * 2));
        }

        // Serialize DOM and set as the response body.
        response.setBody(document.toByteArray());
    }
};

int main(int argc, char *argv[]) {
    // Initiate Qt application
    QCoreApplication a(argc, argv);

    // Set logging mode to output on console
    Log::instance()->setLoggingMode(Log::LoggingModeConsole);

    // Create a web engine
    Http::WebEngine webEngine;
    webEngine.addResource(new Resource());

    // Create and launch a server that for our web engine
    Tcp::MultithreadedServer tcpServer;
    tcpServer.setResponder(&webEngine);
    tcpServer.listen(QHostAddress::Any, 8080, 16);
    if(!tcpServer.isListening()) {
        return 1;
    }

    // Enter event loop
    return a.exec();
}

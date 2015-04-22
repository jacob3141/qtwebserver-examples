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

        // Create a new ul-element
        QDomElement unorderedList = document.createElement("ul");

        // Add list items by manipulating the DOM directly
        for(int i = 0; i < 42; i++) {
            // Create li element
            QDomElement listItem = document.createElement("li");

            // Create text element
            QDomText listItemText = document.createTextNode(
                QString("Item no. %1").arg(i + 1));

            // Append text element to the li element
            listItem.appendChild(listItemText);

            // Append list element to the ul element
            unorderedList.appendChild(listItem);
        }

        // Append the unordered list element to the documents body element
        document.body().appendChild(unorderedList);

        // Serialize DOM and set as the response body
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

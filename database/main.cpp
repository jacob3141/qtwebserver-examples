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
#include "sql/sqlconnectionpool.h"

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

        // Query data from SQL table
        Sql::ConnectionPool& pool = Sql::ConnectionPool::instance();
        QSqlQuery query = pool.exec("SELECT * FROM main.people");

        // Create a table element
        QDomElement tableElement = document.createElement("table");

        // Run through all fetched results
        while (query.next()) {
            // Create a row element for each result
            QDomElement tableRowElement = document.createElement("tr");

            // Extract results from query for this row
            QString idValue = query.value(0).toString();
            QString nameValue = query.value(1).toString();
            QString professionValue = query.value(2).toString();

            // Create td for each data field
            QDomElement tableDataIdElement = document.createElement("td");
            QDomElement tableDataNameElement = document.createElement("td");
            QDomElement tableDataProfessionElement = document.createElement("td");

            // Create text nodes
            QDomText idTextNode = document.createTextNode(idValue);
            QDomText nameTextNode = document.createTextNode(nameValue);
            QDomText professionTextNode = document.createTextNode(professionValue);

            // Append text nodes to table data elements
            tableDataIdElement.appendChild(idTextNode);
            tableDataNameElement.appendChild(nameTextNode);
            tableDataProfessionElement.appendChild(professionTextNode);

            // Append table data elements to table row element
            tableRowElement.appendChild(tableDataIdElement);
            tableRowElement.appendChild(tableDataNameElement);
            tableRowElement.appendChild(tableDataProfessionElement);

            // Append table row element to table element
            tableElement.appendChild(tableRowElement);
        }

        // Finally, add table to the document's body
        document.body().appendChild(tableElement);

        // Serialize DOM and set as the response body
        response.setBody(document.toByteArray());
    }
};

int main(int argc, char *argv[]) {
    // Initiate Qt application
    QCoreApplication a(argc, argv);

    // Set logging mode to output on console
    Log::instance()->setLoggingMode(Log::LoggingModeConsole);

    // Create a connection, so we can keep connections open and can reuse
    // them. This is a lot faster than reopening connections on purpose.
    Sql::ConnectionPool& pool = Sql::ConnectionPool::instance();
    pool.setDatabaseName("example.sqlite");
    pool.setDriverName("QSQLITE");
    if(!pool.open()) {
        // Failed to open connection to database
        return 2;
    }

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

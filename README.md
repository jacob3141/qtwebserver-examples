# Example repository for QtWebServer

This repository demonstrates how to use QtWebServer for building your own web
services with Qt.

## Getting started

On the most popular server distributions like Debian, Ubuntu and the like the Qt runtime will be preinstalled already as an integral part of the system. To write your own applications, you will need to install the Qt5 development packages through apt-get.

On Windows and MacOSX you will need to install the Qt SDK manually from the [Qt website](http://www.qt.io/download-open-source/).

Other than that, there are no other dependencies. It is important you clone the repository with the *--recursive* option to automatically clone the QtWebServer pod, too. Although it is recommended you use QtPods for setting up your own projects, QtPods is *not needed* when cloning an already existing project.

So here we go:
```
git clone --recursive https://github.com/cybercatalyst/qtwebserver-examples.git
```

Open *qtwebserver-examples.pro* with QtCreator and build and run the example projects. It may happen that you once have to build the qtwebserver project manually before building any of the examples, I am investigating on this. Once you have started any of the examples, visit *http://localhost:8080*.

## Description of examples

### database

Demonstrates using the SQL connection pool for reusing database connection. Reads from a database table and displays data in an HTML table. You have to make sure the example.sqlite will be next to the resulting executable to have this example work.

### dataurl

Uses the data url utility methods to encode ans serve an image as a data url. The image is loaded from Qt's resource system.

### dommanipulation

Demonstrates how to access the DOM, adding elements dynamically instead of doing heavy text processing with clumsy templates.

### https

Shows how to create and load your own self-signed certificate to provide a secure connection.

### minimal

A minimal example of what is needed to run a completely self-contained webservice with 16 lightweight server threads.

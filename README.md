Support this and other free software projects of mine by donating bitcoins:
```cpp
1HdLeSj4SfRC77tb6pDUPqeXGiw3T2RqrG
```
[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=9WB9VJA9RGWTN)

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

### Pitfalls and trouble shooting

Usually, the setup should be as mentioned above. Thanks to the feedback of some people I am listing pitfalls and their solutions here, so before falling into despair you might check this list if someone else has encountered your issue before.

#### I get a lot of errors
Check whether you have set your build target to "Desktop". QtCreator will ask you for which targets to build when you're opening a project for the first time. Then it will create a .pro.user file in which it stores all personal settings so you do not have to make that decision each time. If you think have messed up, you can safely close QtCreator, delete this file and reopen the project.

#### Cannot find -lqtwebserver
For some reason the build order is broken (see above). You can easily circumvent this: Rightclick on the qtwebserver project in the project tree (or open the context menu with a two-finger tap) and click "Build qtwebserver". After that has finished, the qtwebserver library will be available and you can build the examples.

#### I cannot start the console application
Sometimes, the terminal settings are messed up and QtCreator is not able to launch the application. This can be (but isn't necessarily) related to using a non-usual shell instead of that one that your system usually uses. At any time, you can launch the application directly from the build folder. If you have not changed settings, your build folder will be named similary to "build-qtwebserver-examples-Ubuntu-Debug" next to the source root directory (called "Out-of-source build"). QtCreator will preserve the original source tree structure by default. If you aren't confident with the location of the build directory, you can change it in the project tab on the left, where you can edit all properties for each target (called a "kit" in QtCreator).

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

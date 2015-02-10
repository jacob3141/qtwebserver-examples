QT       += core network

QT       -= gui

TARGET = serverapp
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

include(../pods.pri)

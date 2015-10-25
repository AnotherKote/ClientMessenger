#-------------------------------------------------
#
# Project created by QtCreator 2015-10-21T22:37:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ClientMessenger
TEMPLATE = app
CONFIG += c++11
RC_FILE = icon.rc

SOURCES += main.cpp \
        private/TrayMenu.cpp \
        private/Settings.cpp \
    private/PopupMessage.cpp

HEADERS += TrayMenu.hpp \
        Settings.hpp \
    PopupMessage.hpp

RESOURCES += \
    images.qrc

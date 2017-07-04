QT -= core
QT -= gui

CONFIG += c++11

TARGET = HIDAPI
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    hidlib/hid-libusb.c \
    hidlib/hidinterface.c \
    main.c

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
#DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    hidlib/hidapi.h \
    hidlib/hidinterface.h

#static

message("$$myPlatform compile")
INCLUDEPATH += $$PWD/lib/$$myPlatform/libusb/include/libusb-1.0/
LIBS += $$PWD/lib/$$myPlatform/libusb/lib/libusb-1.0.a

#dynamic
#INCLUDEPATH += /opt/libusb1.0/include/libusb-1.0
#LIBS += -L"/usr/lib/x86_64-linux-gnu" -lusb-1.0

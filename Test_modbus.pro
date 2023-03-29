QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QT += core network serialbus

TARGET = modbus_server
TEMPLATE = app

SOURCES += main.cpp \
    modbus_srv.cpp \
    qamabstractserver.cpp \
    qammodbusmap.cpp \
    qammodbusdata.cpp \
    qamtcpserver.cpp \
    qamtcpconnection.cpp


HEADERS +=\
    modbus_srv.h \
qamabstractserver.h \
qammodbusmap.h \
qammodbusdata.h \
qamtcpserver.h \
qamtcpconnection.h

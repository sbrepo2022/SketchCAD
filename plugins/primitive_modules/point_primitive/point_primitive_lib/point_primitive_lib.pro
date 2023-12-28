QT -= gui
QT += widgets

TEMPLATE = lib
DEFINES += POINT_PRIMITIVE_LIB_LIBRARY

QMAKE_CXXFLAGS += -std=c++2b

CONFIG += static_lib

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    

HEADERS += \
    point_primitive_lib_global.h
    


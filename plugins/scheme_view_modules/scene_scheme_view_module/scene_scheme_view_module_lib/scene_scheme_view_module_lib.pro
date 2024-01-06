QT -= gui
QT += widgets

TEMPLATE = lib
DEFINES += SCENE_SCHEME_VIEW_MODULE_LIB_LIBRARY

CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(scene_scheme_view_module_lib.pri)

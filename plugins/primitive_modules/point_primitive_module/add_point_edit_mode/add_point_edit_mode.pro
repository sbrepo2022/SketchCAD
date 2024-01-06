QT += widgets

TEMPLATE = lib
DEFINES += ADD_POINT_EDIT_MODE_LIBRARY

CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17

contains(CONFIG, debug) {
    BUILD_MODE = debug
} else {
    BUILD_MODE = release
}

unix {
    BUILD_MODE = .
}

CONFIG += plugin

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include($$PWD/../point_primitive_lib/point_primitive_lib.pri)

SOURCES += \
    add_point_edit_mode_plugin.cpp

HEADERS += \
    add_point_edit_mode_global.h \
    add_point_edit_mode_plugin.h

# Default rules for deployment.
target.path = $$OUT_PWD/../../../../gui/$$BUILD_MODE/plugins
INSTALLS += target

QMAKE_POST_LINK += $(MAKE) install

RESOURCES += \
    resource.qrc


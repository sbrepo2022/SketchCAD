QT += widgets

TEMPLATE = lib
DEFINES += POINT_SCENE_VIEW_ITEM_LIBRARY

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

include($$PWD/../../point_primitive_lib/point_primitive_lib.pri)

SOURCES += \
    point_scene_view_item.cpp

HEADERS += \
    point_scene_view_item.h \
    point_scene_view_item_global.h

# Default rules for deployment.
target.path = $$OUT_PWD/../../../../../gui/$$BUILD_MODE/plugins
INSTALLS += target

QMAKE_POST_LINK += $(MAKE) install

RESOURCES += \
    resource.qrc


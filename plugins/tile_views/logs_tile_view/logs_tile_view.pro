QT += widgets

TEMPLATE = lib
DEFINES += LOGS_TILE_VIEW_LIBRARY

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

SOURCES += \
    logs_tile_view_plugin.cpp

HEADERS += \
    logs_tile_view_global.h \
    logs_tile_view_plugin.h

LIBS += \
    -L$$OUT_PWD/../../../core/$$BUILD_MODE -lcore

INCLUDEPATH += \
    $$PWD/../../../core

DEPENDPATH += \
    $$PWD/../../../core

FORMS += \
    logs_tile_view.ui

# Default rules for deployment.
target.path = $$OUT_PWD/../../../gui/$$BUILD_MODE/plugins
INSTALLS += target

QMAKE_POST_LINK += $(MAKE) install


RESOURCES += \
    resources.qrc


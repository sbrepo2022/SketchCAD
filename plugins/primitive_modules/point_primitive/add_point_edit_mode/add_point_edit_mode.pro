QT += widgets

TEMPLATE = lib
DEFINES += ADDPOINTEDITMODE_LIBRARY

QMAKE_CXXFLAGS += -std=c++2b

contains(CONFIG, debug) {
    BUILD_MODE = debug
} else {
    BUILD_MODE = release
}

CONFIG += plugin

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_point_edit_mode.cpp

HEADERS += \
    add_point_edit_mode.h \
    add_point_edit_mode_global.h

LIBS += \
    -L$$OUT_PWD/../../../../core/$$BUILD_MODE -lcore

INCLUDEPATH += \
    $$PWD/../../../../core

DEPENDPATH += \
    $$PWD/../../../../core

# Default rules for deployment.
mytarget.commands += $${QMAKE_MKDIR} $$shell_path($$OUT_PWD/../../../../gui/$$BUILD_MODE/plugins)
target.path = $$OUT_PWD/../../../../gui/$$BUILD_MODE/plugins
unix {
    target.files = $$OUT_PWD/$$BUILD_MODE/add_point_edit_mode.so
}
win32 {
    target.files = $$OUT_PWD/$$BUILD_MODE/add_point_edit_mode.dll
}
!isEmpty(target.path): INSTALLS += target

QMAKE_POST_LINK += $(MAKE) install

RESOURCES += \
    resource.qrc


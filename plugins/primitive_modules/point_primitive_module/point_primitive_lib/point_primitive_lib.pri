contains(CONFIG, debug) {
    BUILD_MODE = debug
} else {
    BUILD_MODE = release
}

unix {
    BUILD_MODE = .
}

DEFINES += POINT_PRIMITIVE_LIB_LIBRARY

SOURCES += \
    $$PWD/point_graphics_item.cpp \
    $$PWD/point_position_change_action_command.cpp \
    $$PWD/point_primitive.cpp \
    $$PWD/point_properties_component.cpp \
    $$PWD/point_scene_view_item.cpp


HEADERS += \
    $$PWD/point_graphics_item.h \
    $$PWD/point_position_change_action_command.h \
    $$PWD/point_primitive.h \
    $$PWD/point_primitive_lib_global.h \
    $$PWD/point_properties_component.h \
    $$PWD/point_scene_view_item.h

LIBS += \
    -L$$OUT_PWD/../../../../core/$$BUILD_MODE -lcore

INCLUDEPATH += \
    $$PWD/../../../../core \
    $$PWD

DEPENDPATH += \
    $$PWD/../../../../core \
    $$PWD

include($$PWD/../../../scheme_view_modules/scene_scheme_view_module/scene_scheme_view_module_lib/scene_scheme_view_module_lib.pro)

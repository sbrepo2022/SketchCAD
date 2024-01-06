contains(CONFIG, debug) {
    BUILD_MODE = debug
} else {
    BUILD_MODE = release
}

unix {
    BUILD_MODE = .
}

DEFINES += SCENE_SCHEME_VIEW_MODULE_LIB_LIBRARY

SOURCES += \
    $$PWD/abstract_primitive_scene_view_item.cpp \
    $$PWD/scene_scheme_view_model_lib.cpp \
    $$PWD/scheme_graphics_scene.cpp

HEADERS += \
    $$PWD/abstract_primitive_scene_view_item.h \
    $$PWD/scene_scheme_view_model_lib.h \
    $$PWD/scene_scheme_view_module_lib_global.h \
    $$PWD/scheme_graphics_scene.h

LIBS += \
    -L$$OUT_PWD/../../../../core/$$BUILD_MODE -lcore

INCLUDEPATH += \
    $$PWD/../../../../core \
    $$PWD

DEPENDPATH += \
    $$PWD/../../../../core \
    $$PWD

DEFINES += POINT_PRIMITIVE_LIB_LIBRARY

SOURCES += \
    $$PWD/point_graphics_item.cpp \
    $$PWD/point_scene_view_item.cpp


HEADERS += \
    $$PWD/point_graphics_item.h \
    $$PWD/point_primitive_lib_global.h \
    $$PWD/point_scene_view_item.h

LIBS += \
    -L$$OUT_PWD/../../../../core/$$BUILD_MODE -lcore

INCLUDEPATH += \
    $$PWD/../../../../core

DEPENDPATH += \
    $$PWD/../../../../core

include($$PWD/../../../scheme_view_modules/scene_scheme_view_module/scene_scheme_view_module_lib/scene_scheme_view_module_lib.pro)

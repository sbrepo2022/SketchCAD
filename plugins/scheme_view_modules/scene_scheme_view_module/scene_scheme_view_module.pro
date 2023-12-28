TEMPLATE = subdirs

QMAKE_CXXFLAGS += -Wall -Wextra
QMAKE_CFLAGS += -Wall -Wextra

SUBDIRS = \
    scene_scheme_tile_view \
    scene_scheme_view_model \
    scene_scheme_view_module_lib

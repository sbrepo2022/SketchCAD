TEMPLATE = subdirs

QMAKE_CXXFLAGS += -Wall -Wextra
QMAKE_CFLAGS += -Wall -Wextra

SUBDIRS = \
    tile_views \
    primitive_modules \
    scheme_view_modules

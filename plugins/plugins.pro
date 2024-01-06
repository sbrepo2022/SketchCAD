TEMPLATE = subdirs

QMAKE_CXXFLAGS += -Wall -Wextra
QMAKE_CFLAGS += -Wall -Wextra

CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17

SUBDIRS = \
    tile_views \
    primitive_modules \
    scheme_view_modules

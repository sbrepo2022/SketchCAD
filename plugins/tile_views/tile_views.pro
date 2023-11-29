TEMPLATE = subdirs

QMAKE_CXXFLAGS += -Wall -Wextra
QMAKE_CFLAGS += -Wall -Wextra

SUBDIRS = \
    scheme_tile_view \
    logs_tile_view


gui.depends = core

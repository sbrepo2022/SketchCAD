TEMPLATE = subdirs

QMAKE_CXXFLAGS += -Wall -Wextra
QMAKE_CFLAGS += -Wall -Wextra

SUBDIRS = \
    logs_tile_view


gui.depends = core

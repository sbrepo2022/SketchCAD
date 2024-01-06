TEMPLATE = subdirs

QMAKE_CXXFLAGS += -Wall -Wextra
QMAKE_CFLAGS += -Wall -Wextra

CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17

SUBDIRS = \
    logs_tile_view


gui.depends = core

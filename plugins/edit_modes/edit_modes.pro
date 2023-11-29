TEMPLATE = subdirs

QMAKE_CXXFLAGS += -Wall -Wextra
QMAKE_CFLAGS += -Wall -Wextra

SUBDIRS = \
    add_point_edit_mode


gui.depends = core

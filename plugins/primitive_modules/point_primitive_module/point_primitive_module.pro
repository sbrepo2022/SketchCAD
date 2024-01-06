TEMPLATE = subdirs

QMAKE_CXXFLAGS += -Wall -Wextra
QMAKE_CFLAGS += -Wall -Wextra

CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17

SUBDIRS = \
    add_point_edit_mode \
    point_primitive \
    point_selectable_model_component \
    primitive_view_items \
    point_primitive_lib


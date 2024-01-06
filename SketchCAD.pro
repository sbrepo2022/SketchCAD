TEMPLATE = subdirs

QMAKE_CXXFLAGS += -Wall -Wextra
QMAKE_CFLAGS += -Wall -Wextra

CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17

SUBDIRS = \
    core \
    gui \
    plugins

gui.depends = core
plugins.depends = core

GCC_DIR = $$system(which $$QMAKE_CXX)
GCC_VERSION = $$system($$QMAKE_CXX -v 2>&1 | tail -1)

message("Компилятор находится в: $$GCC_DIR")
message("Версия компилятора: $$GCC_VERSION")

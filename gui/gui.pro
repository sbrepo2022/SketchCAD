QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17

contains(CONFIG, debug) {
    BUILD_MODE = debug
} else {
    BUILD_MODE = release
}

unix {
    BUILD_MODE = .
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    tile_widget/tile_widget.cpp

HEADERS += \
    mainwindow.h \
    tile_widget/tile_widget.h

LIBS += \
    -L$$OUT_PWD/../core/$$BUILD_MODE -lcore

INCLUDEPATH += \
    $$PWD/../core

DEPENDPATH += \
    $$PWD/../core

FORMS += \
    mainwindow.ui \
    tile_widget/tile_widget.ui

TRANSLATIONS += \
    translate_ru_RU.ts

RESOURCES += \
    resources.qrc

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

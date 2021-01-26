TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Game.cpp \
        GameData.cpp \
        Table.cpp \
        input.cpp \
        main.cpp \
        output.cpp \
        tools.cpp

HEADERS += \
    Game.h \
    GameData.h \
    Table.h \
    input.h \
    output.h \
    tools.h

DISTFILES += \
    .gitignore

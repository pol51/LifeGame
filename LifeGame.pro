TEMPLATE = app
TARGET = LifeGame
DEPENDPATH += . res src ui src/engine
INCLUDEPATH += . src src/engine

DESTDIR = bin
MOC_DIR = build/moc
UI_DIR = build/uic
OBJECTS_DIR = build/obj
RCC_DIR = build/rcc
RC_FILE += LifeGame.rc

QT += opengl

# Input
HEADERS += src/lifeWidget.h \
           src/QtHud.h \
           src/winGOL.h \
           src/engine/LifeGame.h \
           src/engine/Object.h \
           src/engine/Square.h \
           src/engine/Square8.h \
           src/engine/Table.h \
           src/engine/Table8.h \
           src/engine/Type.h
FORMS += ui/GOL.ui
SOURCES += src/lifeWidget.cpp \
           src/main.cpp \
           src/QtHud.cpp \
           src/winGOL.cpp \
           src/engine/LifeGame.cpp \
           src/engine/Object.cpp \
           src/engine/Square.cpp \
           src/engine/Square8.cpp \
           src/engine/Table.cpp \
           src/engine/Table8.cpp \
           src/engine/Type.cpp
RESOURCES += res/res.qrc

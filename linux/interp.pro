TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
TARGET = interp

QMAKE_CFLAGS += -Wall -std=c17 -Wno-unused-parameter
QMAKE_CFLAGS += -Wno-unused-function -Wno-unused-result

INCLUDEPATH += $$PWD/../include

LIBS += -lpthread
LIBS += -lconfig

SOURCES += \
    ../src/foo1.c \
    ../src/intrinsic.c \
    ../src/main.c \
    ../src/threadpool.c \
    ../src/utils/filesys.c \
    ../src/utils/huff.c

HEADERS += \
    ../include/commands.h \
    ../include/foo1.h \
    ../include/intrinsic.h \
    ../include/parser.h \
    ../include/simple_strlib.h \
    ../include/support.h \
    ../include/threadpool.h \
    ../include/utils/filesys.h \
    ../include/utils/huff.h

CONFIG(release, debug|release) {
    QMAKE_POST_LINK=$(STRIP) $(TARGET)
}

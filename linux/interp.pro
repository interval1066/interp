TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
TARGET = interp

QMAKE_CFLAGS += -Wall -std=c17 -Wno-unused-parameter
QMAKE_CFLAGS += -Wno-unused-function -Wno-unused-result
QMAKE_CFLAGS += -Wno-discarded-qualifiers -Wno-int-conversion
QMAKE_CFLAGS += -Wno-incompatible-pointer-types

INCLUDEPATH += $$PWD/../include

LIBS += -lpthread

SOURCES += \
	../src/foo1.c \
	../src/intrinsic.c \
	../src/support.c \
	../src/main.c \
	../src/support.c \
	../src/utils/filesys.c \
	../src/utils/huff.c \
	../src/utils/config.c

HEADERS += \
	../include/commands.h \
	../include/foo1.h \
	../include/intrinsic.h \
	../include/parser.h \
	../include/simple_strlib.h \
	../include/support.h \
	../include/utils/filesys.h \
	../include/utils/huff.h \
	../include/utils/config.h

CONFIG(release, debug|release) {
QMAKE_POST_LINK=$(STRIP) $(TARGET)
}

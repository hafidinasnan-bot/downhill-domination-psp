
TARGET = downhill
OBJS = src/main.o

INCDIR =
CFLAGS = -G0 -Wall
CXXFLAGS = $(CFLAGS)
ASFLAGS = $(CFLAGS)

LIBS = -lpspdebug -lpspdisplay -lpspge -lpspctrl

BUILD_PRX = 1
PSP_FW_VERSION = 660

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Downhill PSP Prototype

include $(PSPSDK)/lib/build.mak

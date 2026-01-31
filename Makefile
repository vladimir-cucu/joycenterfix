TARGET = joycenterfix
OBJS = src/main.o src/config.o src/hook.o

BUILD_PRX = 1
USE_KERNEL_LIBS = 1

CFLAGS = -O2 -G0 -Wall

PSPSDK := $(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build_prx.mak

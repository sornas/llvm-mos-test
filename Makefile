CC = $(LLVM_MOS)/bin/mos-nes-mmc1-clang
CFLAGS = -flto
CFLAGS_c = -std=gnu23 -Wall -Wextra -Os -g
LINKFLAGS = -Tcommon.ld -Tc-in-prg-ram-0.ld -Tprg-rom-fixed.ld
LINKLIBS = -lneslib -lnesdoug

SRCS := $(shell find -L . -name "*.c" -or -name "*.s")
OBJS := $(SRCS:%=%.o)

all: main.nes

%.c.o: %.c
	$(CC) $(CFLAGS) $(CFLAGS_c) $^ -c -o $@

%.s.o: %.s
	$(CC) $(CFLAGS) $^ -c -o $@

main.nes: $(OBJS)
	$(CC) $(CFLAGS) $^ -o main.nes $(LINKFLAGS) $(LINKLIBS)

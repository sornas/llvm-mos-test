CC = $(LLVM_MOS)/bin/mos-nes-mmc1-clang
CFLAGS = -flto
CFLAGS_c = -std=gnu23 -Wall -Wextra -Os
LINKFLAGS = -Tcommon.ld -Tc-in-prg-ram-0.ld -Tprg-rom-fixed.ld
LINKLIBS = -lneslib -lnesdoug

SRCS := $(shell find -L . -name "*.c" -or -name "*.s")
OBJS := $(SRCS:%=out/%.o)

all: out/main.nes

out/%.c.o: %.c
	mkdir -p "$$(dirname "$@")"
	$(CC) $(CFLAGS) $(CFLAGS_c) $^ -c -o $@

out/%.s.o: %.s
	mkdir -p "$$(dirname "$@")"
	$(CC) $(CFLAGS) $^ -c -o $@

out/main.nes: $(OBJS)
	$(CC) $(CFLAGS) $^ -o out/main.nes $(LINKFLAGS) $(LINKLIBS)

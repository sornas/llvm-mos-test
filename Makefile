CC = $(LLVM_MOS)/bin/mos-nes-mmc1-clang
CFLAGS = -flto
CFLAGS_c = -std=gnu23 -Wall -Wextra -Os
LINKFLAGS = -Tcommon.ld -Tc-in-prg-ram-0.ld -Tprg-rom-fixed.ld
LINKLIBS = -lneslib -lnesdoug

OUTDIR := out

SRCS := $(shell find -L . -name "*.c" -or -name "*.s")
OBJS := $(SRCS:%=out/%.o)

.PHONY: build run clean

build: $(OUTDIR)/main.nes

run: $(OUTDIR)/main.nes
	mesen $(OUTDIR)/main.nes

clean:
	rm -rf $(OUTDIR)/

$(OUTDIR)/%.c.o: %.c
	mkdir -p "$$(dirname "$@")"
	$(CC) $(CFLAGS) $(CFLAGS_c) $^ -c -o $@

$(OUTDIR)/%.s.o: %.s
	mkdir -p "$$(dirname "$@")"
	$(CC) $(CFLAGS) $^ -c -o $@

$(OUTDIR)/main.nes: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(OUTDIR)/main.nes $(LINKFLAGS) $(LINKLIBS)

CC = $(LLVM_MOS)/bin/mos-nes-mmc1-clang
CFLAGS = -std=gnu23 -Wall -Wextra -Os -flto
LINKFLAGS = -Tcommon.ld -Tc-in-prg-ram-0.ld -Tprg-rom-fixed.ld
LINKLIBS = -lneslib -lnesdoug

all: main.nes

main.o: main.c
	$(CC) $(CFLAGS) main.c -c -o main.o

chr.o: chr.s
	$(CC) $(CFLAGS) chr.s -c -o chr.o

main.nes: main.o chr.o
	$(CC) $(CFLAGS) main.o chr.o -o main.nes $(LINKFLAGS) $(LINKLIBS)

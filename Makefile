SRC := src
ASM_DIR := $(SRC)/asm
INC_DIR := include
OUT := out

AS := nasm
AFLAGS := -i$(ASM_DIR) -DARCH_X86_64=1 -Dprivate_prefix=_ -felf64 -g
CC := gcc
CFLAGS := -g -m64 -msse2 -std=c99 -DTESTS
#-I$(INC_DIR) 

all: main

$(OUT):
	mkdir -p $@

$(OUT)/vec_basic.o: $(OUT) 
	$(AS) $(AFLAGS) $(ASM_DIR)/vec_basic.asm -o $@

main: $(OUT)/vec_basic.o $(SRC)/main.c
	$(CC) $(CFLAGS) $(OUT)/vec_basic.o $(SRC)/main.c -o $(OUT)/vec_test

clean:
	rm -rf $(OUT)

#nasm -g -DARCH_X86_64=1 -Dprivate_prefix=_ vec_basic.asm -felf64
#gcc -DTEST2 -g -m64 -msse2 vec_basic.o test.c -o vec_test

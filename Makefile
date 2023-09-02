CFLAGS = -c -Wall -std=c11 -g
LDFLAGS = -lm

SRCS = main.c
OBJS = main.o

ifeq ($(BODY), ASM)
	CFLAGS += -Dasm
	SRCS += process.s
	OBJS += process.o
endif

ifeq ($(OPT), o0)
	CFLAGS += -o0
endif

ifeq ($(OPT), o1)
	CFLAGS += -O1
endif

ifeq ($(OPT), o2)
	CFLAGS += -O2
endif

ifeq ($(OPT), o3)
	CFLAGS += -O3
endif

ifeq ($(OPT), ofast)
	CFLAGS += -Ofast
endif

all: lab $(SRCS)

lab: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o lab
main.o:
	$(CC) $(CFLAGS) main.c -o main.o
process.o: process.s
	nasm -f elf64 -g process.s -o process.o
clean:
	rm -rf $(OBJS)



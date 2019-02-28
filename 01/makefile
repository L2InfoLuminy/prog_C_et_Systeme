SHELL = /bin/sh

CC = clang
CFLAGS = -W -Wall -std=c99 -O2 -pedantic -I . -Iinclude -march=native -pipe -fstack-protector-strong --param=ssp-buffer-size=4
#LDFLAGS = -lm

ifeq ($(DEBUG),1)
	CFLAGS += -g3 -DDEBUG
endif

EXEC = bin/test

SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)

all: build
	@mkdir -p bin

build: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(EXEC) $^

%.o: %.c test/%.c common/%.c components/%.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c $<

.PHONY : clean

clean:
	@rm -vf **/*.o *.o

proper: clean
	@rm `ls bin/* | grep -v "tests"` -f


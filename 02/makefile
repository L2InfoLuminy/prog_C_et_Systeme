CC = clang
CFLAGS = -std=c99 -W -Wall -pedantic -O2 -I. -Iinclude
LIBS = -lm

ifeq ($(DEBUG),1)
	CFLAGS += -g3 -DDEBUG
endif

EXEC = bin/poker
HEADERS = $(wildcard *.h) $(wildcard test/*.h)
SOURCES = $(wildcard *.c) $(wildcard test/*.c)
#MODULES = $(basename $(SOURCES))
#OBJECTS = $(addsuffix .o , $(MODULES))
OBJECTS = $(SOURCES:.c=.o)

$(EXEC): $(OBJECTS)
	@echo === LINKING $@ ===
	$(CC) $^ $(LIBS) -o $@

%.o: %.c test/%.c
	$(CC) $< $(CFLAGS) -c

depend: $(SOURCES) $(HEADERS)
	@echo === COMPUTING $@ ===
	$(CC) -MM $(CFLAGS) $(SOURCES) > $@

.PHONY : clean proper

clean:
	@echo CLEANING ===
	@rm -vf **/*.o *.o

proper: clean
	@rm -vf `ls bin/*`

-include depend


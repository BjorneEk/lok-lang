TARGET = lok-lang

CC = gcc
INCLUDE_DIR = src
CFLAGS = -I$(INCLUDE_DIR)
C_SOURCES = $(wildcard src/*.c *.c )
DEPS = $(wildcard $(INCLUDE_DIR)/*.h *.h)
OBJ = ${C_SOURCES:.c=.o}

# First rule is the one executed when no parameters are fed to the Makefile


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	$(RM) src/*.bin src/*.o src/*.dis src/*.elf
	$(RM) lib/*.o

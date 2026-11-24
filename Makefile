CC ?= gcc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -O2
TARGET = ordenamiento
SOURCES = main.c metodos_Ordenamiento.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SOURCES) metodos_Ordenamiento.h
	$(CC) $(CFLAGS) $(SOURCES) -o $@

clean:
	rm -f $(TARGET)

CC=gcc
CFLAGS=-Wall -g
TARGET=mysh
SOURCES=mysh_main.c mysh_utils.c mysh_pipeline.c
OBJECTS=$(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

%.o: %.c mysh.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: all clean
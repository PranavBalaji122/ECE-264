# Makefile

CC       := gcc
CFLAGS   := -std=c11 -g -Wall -Wshadow -pedantic -Wvla -Werror

SRCS     := main.c practica_c.c
OBJS     := $(SRCS:.c=.o)
TARGET   := practica

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

main.o: main.c practica_c.h
	$(CC) $(CFLAGS) -c main.c

practica_c.o: practica_c.c practica_c.h
	$(CC) $(CFLAGS) -c practica_c.c

clean:
	rm -f $(OBJS) $(TARGET)

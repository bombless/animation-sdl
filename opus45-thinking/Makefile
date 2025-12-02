CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -lSDL2

# 检测操作系统
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
    CFLAGS += $(shell sdl2-config --cflags)
    LDFLAGS = $(shell sdl2-config --libs)
endif

TARGET = animation
SRCS = main.c render.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c render.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

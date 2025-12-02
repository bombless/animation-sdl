CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -lSDL2

# 检测操作系统
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    # macOS
    CFLAGS += $(shell sdl2-config --cflags)
    LDFLAGS = $(shell sdl2-config --libs)
endif
ifeq ($(UNAME_S),Linux)
    # Linux
    CFLAGS += $(shell sdl2-config --cflags)
    LDFLAGS = $(shell sdl2-config --libs)
endif

TARGET = rectangle_demo
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

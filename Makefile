ifeq ($(OS), Windows_NT)
	CC = gcc
else
	CC = clang
endif

FLAGS = -Wall -Werror -Wpedantic -std=c99 -Iinclude
TARGET = ck
BINDIR = bin
SRC = src/*.c
BUDDY = include/buddy.h

all: $(BUDDY) $(TARGET) 

$(TARGET): $(BINDIR)
	$(CC) $(FLAGS) -o $(BINDIR)/$(TARGET) $(SRC)

$(BINDIR):
	mkdir -p $(BINDIR)

$(BUDDY):
	curl -fsSL https://raw.githubusercontent.com/jesperkha/buddy/refs/heads/main/install.sh | bash
	mv buddy.h include/
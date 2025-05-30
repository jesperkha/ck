ifeq ($(OS), Windows_NT)
	CC = gcc
else
	CC = clang
endif

FLAGS = -Wall -Werror -Wpedantic -std=c99 -Iinclude
RELEASE_FLAGS = -O3
TARGET = ck
BINDIR = bin
SRC = src/*.c
BUDDY = include/buddy.h

all: $(BUDDY) $(TARGET) 

release: $(BUDDY) $(BINDIR)
	$(CC) $(FLAGS) $(RELEASE_FLAGS) -o $(BINDIR)/$(TARGET) $(SRC)

$(TARGET): $(BINDIR)
	$(CC) $(FLAGS) -o $(BINDIR)/$(TARGET) $(SRC)

$(BINDIR):
	mkdir -p $(BINDIR)

$(BUDDY):
	curl -fsSL https://raw.githubusercontent.com/jesperkha/buddy/refs/heads/main/install.sh | bash
	mv buddy.h include/


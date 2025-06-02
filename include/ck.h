#pragma once

#include "buddy.h"
#include <stddef.h> // NULL

#ifdef OS_WINDOWS

#include <windows.h>

#else

#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#endif

#define DEFAULT_LINE_CAP 128

typedef struct Line
{
    int length;
    int cap;
    char *text; // Raw line text content
    bool err;
} Line;

typedef struct Buffer
{
    Allocator a; // Parent allocator and to be used internally (heap)
    bool err;

    int col;       // Cursor col
    int row;       // Cursor row
    int linecount; // Number of non-empty lines
    int linecap;
    Line *lines;
} Buffer;

typedef struct Editor
{
    Buffer *buf;
    int width;  // Width of screen buffer
    int height; // Height of screen buffer

#ifdef OS_WINDOWS
    HANDLE hconsole; // Console screen buffer
#endif
} Editor;

typedef struct Error
{
    String msg; // Temp allocated
    bool empty; // Non-error
} Error;

// Create new temp allocated error.
Error new_error(const char *msg);

#define NO_ERROR ((Error){.empty = true})

// Initialize ck
Error init(void);
// Run main loop in ck
Error run(void);

// Allocate and initialize new buffer.
Buffer *buf_new(Allocator a);
// Free all memory assosiated with the buffer and the buffer itself.
void buf_destroy(Buffer *b);

void term_get_size(void);
void term_set_cursor(int x, int y);
void term_cursor_visible(bool visible);
void term_write(char *string, int length);
void term_set_raw_mode(void);
char get_user_input(void);


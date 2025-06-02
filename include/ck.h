#pragma once

#include "buddy.h"

#ifdef OS_WINDOWS
#include <windows.h>
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

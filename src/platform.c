#include "ck.h"

extern Editor e;

void term_update_size(void)
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(e.hconsole, &info);

    short bufferW = info.dwSize.X;
    short windowH = info.srWindow.Bottom - info.srWindow.Top + 1;

    // Remove scrollbar by setting buffer height to window height
    COORD newSize;
    newSize.X = bufferW;
    newSize.Y = windowH;
    SetConsoleScreenBufferSize(e.hconsole, newSize);

    e.width = (int)(newSize.X);
    e.height = (int)(newSize.Y);
}

void term_set_cursor(int x, int y)
{
    COORD pos = {x, y};
    SetConsoleCursorPosition(e.hconsole, pos);
}

void term_cursor_visible(bool visible)
{
    CONSOLE_CURSOR_INFO info = {100, visible};
    SetConsoleCursorInfo(e.hconsole, &info);
}

void term_write(char *string, int length)
{
    DWORD written;
    if (!WriteConsoleA(e.hconsole, string, length, &written, NULL) || (int)written != length)
        panic_fmt("Failed to write to screen buffer. Length {i32}, written {i32}", length, (int)written);
}

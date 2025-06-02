#include "ck.h"

extern Editor e;

void term_get_size(void)
{
#ifdef OS_WINDOWS
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
#else // FIXME: WSL not defined in buddy
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) < 0)
        panic("failed to get window size");
    else
    {
        e.width = ws.ws_col;
        e.height = ws.ws_row;
    }
#endif
}

void term_set_cursor(int x, int y)
{
#ifdef OS_WINDOWS
    COORD pos = {x, y};
    SetConsoleCursorPosition(e.hconsole, pos);
#else
    printf("\033[%d;%dH", y+1, x+1);
    fflush(stdout);
#endif
}

void term_cursor_visible(bool visible)
{
#ifdef OS_WINDOWS
    CONSOLE_CURSOR_INFO info = {100, visible};
    SetConsoleCursorInfo(e.hconsole, &info);
#else
    if (visible)
        printf("\033[?25h");
    else
        printf("\033[?25l");
    fflush(stdout);
#endif
}

void term_write(char *string, int length)
{
#ifdef OS_WINDOWS
    DWORD written;
    if (!WriteConsoleA(e.hconsole, string, length, &written, NULL) || (int)written != length)
        panic_fmt("failed to write to screen buffer. Length {i32}, written {i32}", length, (int)written);
#else
    ssize_t written = write(STDOUT_FILENO, string, length);
    if (written != length)
        panic_fmt("failed to write to screen buffer. Length {i32}, written {i32}", length, (int)written);
#endif
}

void term_set_raw_mode(void)
{
    // TODO: raw mode (both)
}

char get_user_input(void)
{
#ifdef OS_WINDOWS
    // TODO: windows user input
#else
    char c;
    if (read(STDIN_FILENO, &c, 1) < 0)
        panic("failed to read input");

    return c;
#endif
}


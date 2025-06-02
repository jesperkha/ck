#include "ck.h"

extern Editor e;

// Allocate and initialize new buffer.
Buffer *buf_new(Allocator a)
{
    Buffer *b = alloc(a, sizeof(Buffer));
    if (b == NULL)
        panic("failed to allocate new buffer");

    b->a = a;
    b->col = b->row = 0;
    b->err = false;
    b->linecap = DEFAULT_LINE_CAP;
    b->linecount = 0;

    b->lines = alloc(a, sizeof(Line) * b->linecap);
    if (b->lines == NULL)
        panic("failed to allocate line array");

    return b;
}

// Free all memory assosiated with the buffer and the buffer itself.
void buf_destroy(Buffer *b)
{
    alloc_free(b->a, b);
}

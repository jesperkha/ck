#include "ck.h"

Editor e;

#define BUFFER_POOL_SIZE MB(2)

Error init(void)
{
    Allocator heap = get_heap_allocator();
    Allocator pool = get_pool_allocator(heap, BUFFER_POOL_SIZE);
    e.buf = buf_new(pool);

    term_get_size();
    return NO_ERROR;
}

Error run(void)
{

    return NO_ERROR;
}

Error clean(void)
{
    buf_destroy(e.buf);
    return NO_ERROR;
}

// :util

Error new_error(const char *msg)
{
    return (Error){
        .empty = false,
        .msg = str_temp(msg),
    };
}

// :buffer

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
    free_pool(&b->a);
}

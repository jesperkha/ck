#define BUDDY_IMPLEMENTATION
#include "ck.h"

int main(void)
{
    Error err = init();
    if (!err.empty)
        panic_fmt("init: {s}", err.msg);

    err = run();
    if (!err.empty)
        panic_fmt("run: {s}", err.msg);

    return 0;
}

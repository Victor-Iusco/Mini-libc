#include <stdio.h>
#include <string.h>
#include <internal/syscall.h>

int puts(const char *str)
{
    int len = strlen(str);
    syscall(1, 1, str, len);
    syscall(1, 1, "\n", 1);
    return len;
}

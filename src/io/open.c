// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int open(const char *filename, int flags, ...)
{
	mode_t mode = 0;

    // Check if O_CREAT is in flags to determine if mode is needed
    va_list args;
    if (flags & O_CREAT) {
        va_start(args, flags);
        mode = va_arg(args, mode_t);
        va_end(args);
    }
    long fd;
    if (flags & O_CREAT){
        fd = syscall(__NR_open, filename, flags, mode);
    }else{
        fd = syscall(__NR_open, filename, flags);
    }
    if (fd < 0) {
        errno =-fd;
        return -1;
    }
    return fd;
}

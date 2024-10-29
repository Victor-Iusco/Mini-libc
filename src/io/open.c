// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int open(const char *filename, int flags, ...)
{
	mode_t mode = 0;

    // Check if O_CREAT is in flags to determine if mode is needed
    if (flags & O_CREAT) {
        va_list args;
        va_start(args, flags);
        mode = va_arg(args, mode_t);
        va_end(args);
    }

    // Make the syscall to open the file
    int fd = syscall(2, filename, flags, mode);

    if (fd == -1) {
        // Error encountered, errno is automatically set
        return -1;
    }

    return fd;
}

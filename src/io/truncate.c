// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>

int truncate(const char *path, off_t length)
{
	int result = syscall(76, path, length);

    if (result == -1) {
        // Error encountered, errno is automatically set
        return -1;
    }
    return 0;
}

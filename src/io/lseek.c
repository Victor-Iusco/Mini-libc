// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>

off_t lseek(int fd, off_t offset, int whence)
{
    if (whence != SEEK_SET && whence != SEEK_CUR && whence != SEEK_END) {
        errno = EINVAL;
        return (off_t)-1;
    }

    if (whence == SEEK_SET && offset < 0) {
        errno = EINVAL;
        return (off_t)-1;
    }

	long result = syscall(__NR_lseek, fd, offset, whence);

    if (result < 0) {
        errno = -result;
        return (off_t)-1;
    }

    return (off_t)result;
}

// SPDX-License-Identifier: BSD-3-Clause
#include <sys/mman.h>
#include <errno.h>
#include <internal/syscall.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
    if (!((flags & MAP_SHARED) || (flags & MAP_PRIVATE)))
    {
        errno = EINVAL;
        return MAP_FAILED;
    }
	long a = syscall(__NR_mmap, addr, length, prot, flags, fd, offset);

    if (a < 0)
    {
        errno = -a;
        return MAP_FAILED;
    }
    return (void *)a;
}

void *mremap(void *old_address, size_t old_size, size_t new_size, int flags)
{
    return (void *)syscall(__NR_mremap, old_address, old_size, new_size, flags);
}

int munmap(void *addr, size_t length)
{
    return (int)syscall(__NR_munmap, addr, length);
}


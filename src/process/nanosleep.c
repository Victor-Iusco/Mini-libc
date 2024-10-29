#include <time.h>
#include <stddef.h>
#include <errno.h>
#include <internal/syscall.h>

int nanosleep(const struct timespec *time, struct timespec *time_remaining)
{
    if (time == NULL || time->tv_sec < 0 || time->tv_nsec < 0 || time->tv_nsec > 999999999)
    {
        errno = EINVAL;
        return -1;
    }

    return syscall(35, time, time_remaining);
}



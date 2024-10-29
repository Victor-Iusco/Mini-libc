#include<internal/types.h>

typedef long time_t;

struct timespec {
    time_t tv_sec;
    long tv_nsec;
};

int nanosleep(const struct timespec *time, struct timespec *time_remaining);

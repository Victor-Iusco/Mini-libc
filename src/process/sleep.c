#include<time.h>
#include<errno.h>
#include<stddef.h>
#include<unistd.h>

unsigned int sleep(unsigned int sec)
{
    struct timespec time, time_remaining;

    time.tv_sec = sec;
    time.tv_nsec = 0;

    while (nanosleep (&time, &time_remaining) == -1)
        time_remaining = time;

    return 0;
}

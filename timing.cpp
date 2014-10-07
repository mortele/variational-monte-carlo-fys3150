#include <timing.h>


/**
 * Computes the time since 1 Januray 1970 in milliseconds.
 *
 * @return time since UNIX epoch in milliseconds
 */
ullint unixTimeInMicroseconds() {
    timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return (ullint)ts.tv_sec  * 1000000LL + (ullint)ts.tv_nsec / 1000LL;
}

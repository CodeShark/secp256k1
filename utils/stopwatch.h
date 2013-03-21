// Build using -lrt

#ifndef _STOPWATCH_H_
#define _STOPWATCH_H_

#include <time.h>
#include <stdint.h>

class Stopwatch
{
private:
    struct timespec start, stop;

public:
    int Start(clockid_t clockid = CLOCK_REALTIME) {
        return clock_gettime(clockid, &start);        
    }

    int Stop(clockid_t clockid = CLOCK_REALTIME) {
        return clock_gettime(clockid, &stop);
    }

    uint64_t nsec() {
        return (uint64_t)(stop.tv_sec - start.tv_sec) * 1000000000ULL + stop.tv_nsec - start.tv_nsec;
    }

    double sec() {
        return (double)(stop.tv_sec - start.tv_sec) + (double)(stop.tv_nsec - start.tv_nsec) / 1000000000.0;
    }
};

#endif

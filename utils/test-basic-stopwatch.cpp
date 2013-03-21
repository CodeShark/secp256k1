#include <iostream>
#include "stopwatch.h"

using namespace std;

void doCount(uint64_t c) {
    cout << "Adding numbers 0 to " << c << "..." << endl;
    uint64_t k = 0;
    Stopwatch sw_realtime;
    Stopwatch sw_monotonic;
    Stopwatch sw_process_cputime;
    Stopwatch sw_thread_cputime;
    sw_realtime.Start(CLOCK_REALTIME);
    sw_monotonic.Start(CLOCK_MONOTONIC);
    sw_process_cputime.Start(CLOCK_PROCESS_CPUTIME_ID);
    sw_thread_cputime.Start(CLOCK_THREAD_CPUTIME_ID);
    for (uint64_t i = 0; i < c; i++) k += i;
    sw_realtime.Stop(CLOCK_REALTIME);
    sw_monotonic.Stop(CLOCK_MONOTONIC);
    sw_process_cputime.Stop(CLOCK_PROCESS_CPUTIME_ID);
    sw_thread_cputime.Stop(CLOCK_THREAD_CPUTIME_ID);

    cout.precision(9);
    cout << "CLOCK_REALTIME            " << fixed << sw_realtime.sec() << "s" << endl;
    cout << "CLOCK_MONOTONIC           " << fixed << sw_monotonic.sec() << "s" << endl;
    cout << "CLOCK_PROCESS_CPUTIME_ID  " << fixed << sw_process_cputime.sec() << "s" << endl;
    cout << "CLOCK_THREAD_CPUTIME_ID   " << fixed << sw_thread_cputime.sec() << "s" << endl;
}

int main()
{
    doCount(1000000000);
    return 0;
}

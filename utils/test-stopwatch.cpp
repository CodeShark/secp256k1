#include <iostream>
#include "stopwatch.h"
#include <boost/thread.hpp>
#include <pthread.h>

using namespace std;

uint64_t doWork(uint64_t c) {
    uint64_t k = 0;
    for (uint64_t i = 0; i < c; i++) k += i;
    return k;
}

void doCount(uint64_t c, clockid_t clockid) {
    pthread_t thread = pthread_self();
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);
    int s = pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
    if (s != 0) {
        cout << "Error setting thread affinity: " << s << endl;
    }
    cout << "Adding numbers 0 to " << c << "..." << flush;
    uint64_t k = 0;
    Stopwatch sw;
    sw.Start(clockid);
    for (uint64_t i = 0; i < c; i++) k += i;
    sw.Stop(clockid);
    cout.precision(9);
    cout << fixed << sw.sec() << "s" << endl;
}

int main()
{
    cout << "Starting worker thread 1..." << endl;
    boost::thread worker1(doWork, 200000000000ULL);

    cout << "Starting worker thread 2..." << endl;
    boost::thread worker2(doWork, 200000000000ULL);

    cout << "Starting worker thread 3..." << endl;
    boost::thread worker3(doWork, 200000000000ULL);

    cout << endl;

    cout << "Testing CLOCK_REALTIME..." << endl;
    doCount(1000000, CLOCK_REALTIME);
    doCount(10000000, CLOCK_REALTIME);
    doCount(100000000, CLOCK_REALTIME);
    doCount(1000000000, CLOCK_REALTIME);
    cout << "------------------------" << endl << endl;

    cout << "Testing CLOCK_MONOTONIC..." << endl;
    doCount(1000000, CLOCK_MONOTONIC);
    doCount(10000000, CLOCK_MONOTONIC);
    doCount(100000000, CLOCK_MONOTONIC);
    doCount(1000000000, CLOCK_MONOTONIC);
    cout << "------------------------" << endl << endl;

    cout << "Testing CLOCK_PROCESS_CPUTIME_ID..." << endl;
    doCount(1000000, CLOCK_PROCESS_CPUTIME_ID);
    doCount(10000000, CLOCK_PROCESS_CPUTIME_ID);
    doCount(100000000, CLOCK_PROCESS_CPUTIME_ID);
    doCount(1000000000, CLOCK_PROCESS_CPUTIME_ID);
    cout << "------------------------" << endl << endl;

    cout << "Testing CLOCK_THREAD_CPUTIME_ID..." << endl;
    doCount(1000000, CLOCK_THREAD_CPUTIME_ID); 
    doCount(10000000, CLOCK_THREAD_CPUTIME_ID);
    doCount(100000000, CLOCK_THREAD_CPUTIME_ID); 
    doCount(1000000000, CLOCK_THREAD_CPUTIME_ID);  
    cout << "------------------------" << endl << endl;

    return 0;
}

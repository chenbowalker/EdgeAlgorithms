/**
 * g++ thread_atomic.cc -std=c++11 -lpthread
 *
 */

#include <thread>
#include <atomic>
#include <iostream>
#include <unistd.h>
using namespace std;

#define COUNT 10000
/**
static void inc(atomic<int> *p) {
    for (int i = 0; i < COUNT; i++) {
        (*p)++;
    }
}

void threadDataRacing(void) {
    atomic<int> a(0);
    thread ta(inc, &a);
    thread tb(inc, &a);
    ta.join();
    tb.join();
    cout << "a=" << a << endl;
}

int main() {
    threadDataRacing();
    return 0;
}
*/
int mutex = 0;
int lock = 0;
int unlock = 1;
/**
class Lock {
#define LOCK 0
#define UNLOCK 1
    int mutex;

    Lock() : mutex(0) {}

    void lock() {
        while (!(__sync_bool_compare_and_swap(&mutex, LOCK, 1)))
            ;
    }

    void unlock() { __sync_bool_compare_and_swap(&mutex, UNLOCK, 0); }

    bool try_lock() { return 0; }

#undef LOCK
#undef UNLOCK

}; */
int count = 0;
/** for (int i = 0; i < COUNT; i++) {
       __sync_fetch_and_add(&count, 1);
       //count++;
    } */

//__sync_bool_compare_and_swap
void inc() {
    for (int i = 0; i < COUNT; i++) {
        while (!(__sync_bool_compare_and_swap(&mutex, lock, 1)))
            //     usleep(1000);
            //      __sync_bool_compare_and_swap(&mutex, lock, 1);
            count++;
        __sync_bool_compare_and_swap(&mutex, unlock, 0);
    }
    /**
    for (int i = 0; i < COUNT; i++)
        count++;*/
}

int main() {
    // thread t1(inc);
    thread T[10];
    for (int i = 0; i < 10; i++) {
        T[i] = thread(inc);
    }
    for (auto &th : T) {
        th.join();
    }
    cout << count;
    return 0;
}

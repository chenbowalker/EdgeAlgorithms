#include <iostream>
#include <atomic>
#include <thread>

#define COUNT 10000000
using namespace std;
class Thread {
  public:
    void atomic_add(atomic<int> *p) {
        for (int i = 0; i < COUNT; i++) {
            (*p)++;
        }
    }
};


int main() {
    atomic<int> a(0);
    Thread th;
    thread *T[10];
    for (int i = 0; i < 10; i++) {
        T[i] = new thread(&Thread::atomic_add, th, &a);
    }
    for (int j = 0; j < 10; j++) {
        T[j]->join();
    }
    cout << a;
}

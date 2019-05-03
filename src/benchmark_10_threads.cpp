#include "threadweaver.hpp"
#include <iostream>

int main () {
    TRW::ThreadScheduler ts(10);

    for (int i = 0; i < 1000; i++) 
        ts.runFunction([] () {
            for (volatile long j = 0; j < 100000000; j++) {
            }
        });

    ts.waitUntilAllDone();
}
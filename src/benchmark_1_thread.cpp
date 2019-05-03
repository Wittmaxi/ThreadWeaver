#include "threadweaver.hpp"
#include <iostream>

int main () {
    TRW::ThreadScheduler ts(1);

    for (int i = 0; i < 1000; i++) 
        ts.runFunction([] () {
            for (volatile long j = 0; j < 10000000; j++) {
            }
        });

    ts.waitUntilAllDone();
}
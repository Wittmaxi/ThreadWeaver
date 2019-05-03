#include "threadweaver.hpp"
#include <iostream>

int main () {
    TRW::ThreadScheduler ts(10);

    for (int i = 0; i < 100; i++) 
        ts.runFunction([=] () {
            for (int j = 0; j < 100000; j++) 
                ;
            std::cout << "thread 1 id " << i << " done\n";
        });

    ts.waitUntilAllDone();
    std::cout << "\n\n\n\n\n\n\n\n\n\nfirst resize\n\n\n\n\n\n\n\n\n\n";
    ts.resize(11);
    
    for (int i = 0; i < 100; i++) 
        ts.runFunction([=] () {
            for (int j = 0; j < 100000; j++) 
                ;
            std::cout << "thread 2 id " << i << " done\n";
        });

    ts.waitUntilAllDone();
    std::cout << "\n\n\n\n\n\n\n\n\n\nsecond resize \n\n\n\n\n\n\n\n\n\n";
    ts.resize(3);

    for (int i = 0; i < 100; i++) 
        ts.runFunction([=] () {
            for (int j = 0; j < 100000; j++) 
                ;
            std::cout << "thread 3 id " << i << " done\n";
        });

    ts.waitUntilAllDone();



}
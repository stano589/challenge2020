#include <thread>
#include "task1/mylock.hpp"
#include <vector>
#include <cassert>

#define MAX_THREADS 10
#define INCREMENT   1000000

int var = 0;
std::mutex mtx;

void threadFunc(void){
    for(int i=0; i<INCREMENT;  i++){
        /**
         * If we disable the lock, we can see that the sum is less
         * than expected due to write race conditions
         * */
        Mylock::lock_guard<std::mutex> lock(mtx);
        var++;
    }
}

int main(void){

    /*
    * This will run a while...
    */

    std::vector<std::thread> threads;
    for(int i=0; i<MAX_THREADS; i++){
        threads.push_back(std::thread(threadFunc));
    }

    for(int i=0; i<MAX_THREADS; i++){
        threads[i].join();
    }

    printf("Var: %d\n", var);
    assert(var == MAX_THREADS * INCREMENT);

    return 0;
}
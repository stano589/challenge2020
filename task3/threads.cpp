#include <cstdio>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unistd.h>

std::condition_variable cv1,cv2,cv3;
std::mutex mtx;

void thr1func(){
	while(1){
		std::unique_lock<std::mutex> my_lock(mtx);
		cv1.wait(my_lock);
		printf("Thread 1 doing some work...\n");
		sleep(2);
		cv2.notify_one();
	}
}

void thr2func(){
	while(1){
		std::unique_lock<std::mutex> my_lock(mtx);
		cv2.wait(my_lock);
		printf("Thread 2 doing some work...\n");
		sleep(1);
		cv3.notify_one();
	}
}

void thr3func(){
	while(1){
		std::unique_lock<std::mutex> my_lock(mtx);
		cv3.wait(my_lock);
		printf("Thread 3 doing some work...\n");
		sleep(2);
		cv1.notify_one();
	}
}

int main(void){

	// create the treads
	std::thread thr1(thr1func);
	std::thread thr2(thr2func);
	std::thread thr3(thr3func);

	// Wake up the first one and start the sequence
	cv1.notify_all();

	thr1.join();
	thr2.join();
	thr3.join();

	return 0;
}
#include <cstdlib>
#include <cstdio>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <unistd.h>
#include <ctime>

#define MAX_ELEMENTS 100

std::queue<int> shared_vector;

std::mutex mtx;
std::condition_variable cond_var1, cond_var2;

void producer(int id){
	while(1){
		std::unique_lock<std::mutex> my_lock(mtx);
		// if the queue is full, wait
		cond_var2.wait(my_lock, [id]{ printf("Producer %d waiting...\n",id); return shared_vector.size() < MAX_ELEMENTS; });
		printf("%d Producing...\n", id);
		shared_vector.push(rand() % 100);
		// element was produced, notify a consumer
		cond_var1.notify_one();
	}
}

void consumer(int id){
	while(1){
		std::unique_lock<std::mutex> my_lock(mtx);
		// if queue is empty, wait
		cond_var1.wait(my_lock, []{ return !shared_vector.empty(); } );
		printf("%d Consuming...%d\n",id,shared_vector.front());
		shared_vector.pop();
		// element was processed, notify a producer
		cond_var2.notify_one();
	}
}

int main(void){

	srand(time(0));

	// create producers
	std::thread prod1(producer, 1);
	std::thread prod2(producer, 2);

	// sleep for 1s and create consumers
	sleep(1);
	std::thread con1(consumer, 1);
	std::thread con2(consumer, 2);

	prod1.join();
	prod2.join();
	con1.join();
	con2.join();

	return 0;
}
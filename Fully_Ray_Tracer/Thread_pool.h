#pragma once
#include <atomic>
#include <functional>
#include "Thread_joiner.h"
#include "Threadsafe_queue.h"

class Thread_pool {
public:
	Thread_pool();

	template<typename FunctionType>
	void submit(FunctionType f) {
		work_queue.push(std::function<void()>(f));
		data_cond.notify_one();
	}
	void start();

	void wait_and_stop();


	~Thread_pool() { wait_and_stop(); }

private:
	void worker_thread();

	std::atomic_bool running = false;
	std::atomic_bool will_stop = false;
	unsigned thread_count;
	std::condition_variable data_cond;
	std::mutex mtx;
	Threadsafe_queue<std::function<void()>> work_queue;
	std::vector<std::thread> threads;
	Thread_joiner joiner;
};
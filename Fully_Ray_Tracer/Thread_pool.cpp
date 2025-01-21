#include "Thread_pool.h"

Thread_pool::Thread_pool() :joiner(threads), thread_count(int(std::thread::hardware_concurrency()) - 2) {
	thread_count = (thread_count > 0) ? thread_count : 1;
}

void Thread_pool::start() {
	if (running)
		return;
	running = true;
	will_stop = false;
	try {
		for (unsigned i = 0; i < thread_count; i++)
			threads.emplace_back(&Thread_pool::worker_thread, this);
	}
	catch (...) {
		running = false;
		will_stop = true;
		throw;
	}
}

void Thread_pool::wait_and_stop() {
	{
		std::unique_lock<std::mutex> lock(mtx);
		will_stop = true;
	}
	data_cond.notify_all();
	joiner.join();
	running = false;
}

void Thread_pool::worker_thread() {
	while (!will_stop || !work_queue.empty()) {
		std::function<void()> task;
		{
			std::unique_lock<std::mutex>lock(mtx);
			data_cond.wait(lock, [&] {return !work_queue.empty() || will_stop; });
			work_queue.try_pop(task);
		}
		if (task)
			task();
	}
}
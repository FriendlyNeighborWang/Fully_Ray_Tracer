#pragma once
#include <condition_variable>
#include <queue>
#include <mutex>

template<typename T>
class Threadsafe_queue {
public:
	Threadsafe_queue(){}
	
	void push(T new_value) {
		std::lock_guard<std::mutex> lock(mtx);
		data_queue.push(new_value);
		data_cond.notify_one();
	}
	void pop(T& value) {
		std::unique_lock<std::mutex> lock(mtx);
		data_cond.wait(lock, [this] {return !data_queue.empty(); });
		value = std::move(data_queue.front());
		data_queue.pop();
	}
	T pop() {
		std::unique_lock<std::mutex> lock(mtx);
		data_cond.wait(lock, [this] {return !data_queue.empty(); });
		T value = std::move(data_queue.front());
		data_queue.pop();
		return value;
	}

	bool try_pop(T& value) {
		std::lock_guard<std::mutex> lock(mtx);
		if (data_queue.empty())
			return false;
		value = std::move(data_queue.front());
		data_queue.pop();
		return true;
	}
	bool empty() {
		std::lock_guard<std::mutex> lock(mtx);
		return data_queue.empty();
	}
	unsigned size() {
		std::lock_guard<std::mutex> lock(mtx);
		return data_queue.size();
	}

private:
	std::mutex mtx;
	std::queue<T> data_queue;
	std::condition_variable data_cond;
};
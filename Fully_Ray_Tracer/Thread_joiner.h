#pragma once
#include <thread>
#include <vector>

class Thread_joiner {
public:
	Thread_joiner(std::vector<std::thread>& list):thread_list(list){}
	void join() {
		for (auto& th : thread_list) {
			if (th.joinable())
				th.join();
		}
	}
	~Thread_joiner() {
		join();
	}
private:
	std::vector<std::thread>& thread_list;
};
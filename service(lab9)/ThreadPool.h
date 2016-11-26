#pragma once
#include <mutex>
#include <iostream>
#include <cmath>
#include <thread>
#include <future>
#include <functional>
#include <list>
#include <vector>
class ThreadPool
{
private:
	std::mutex m;
	std::list<std::packaged_task<void()>> tasks;
	std::vector<std::thread> threads;
	std::condition_variable cv;
	//bool stop;
	std::atomic<bool> stop;

	void dowork();
	std::packaged_task<void()> fetchtask();
	
public:
	void stopme();
	
	bool addtask(std::packaged_task<void()>&& a);
	void start(int num);
	

	ThreadPool();
	~ThreadPool();
};


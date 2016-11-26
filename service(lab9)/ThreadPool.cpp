#include "stdafx.h"
#include "ThreadPool.h"


ThreadPool::ThreadPool()
{
}

bool ThreadPool::addtask(std::packaged_task<void()>&& a)
{
	std::lock_guard<std::mutex> ml(m);
	tasks.push_back(std::move(a));
	return true;
}

void ThreadPool::start(int num)
{
	stop = false;
	for (int i = 0;i < num;i++)
	{
		std::thread t(&ThreadPool::dowork, this);
		threads.push_back(std::move(t));
	}
}

void ThreadPool::dowork()
{
	try
	{
		for (;!stop;)
		{
			auto r = fetchtask();
			r();
		}
	}
	catch (...) { return; }
}

void ThreadPool::stopme()
{
	stop = true;
	for (auto &i : threads)
	{
		i.join();
	}

}

std::packaged_task<void()> ThreadPool::fetchtask()
{
	std::lock_guard<std::mutex> ms(m);
	if (tasks.empty())
	{
		throw std::runtime_error("tasks empty");
	}
	auto t = std::move(tasks.front());
	tasks.pop_front();
	return t;

}

ThreadPool::~ThreadPool()
{
}

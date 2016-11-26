// service(lab9).cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include "solver.h"
#include "ThreadPool.h"
#include <chrono>
#include <fstream>

using namespace std;



int main(void) {
	initialise();
	auto curTime = chrono::system_clock::now();
	cout << solveOne(10, 10) << endl;


	std::vector<std::pair<int, int>> v;// = {{10,10}, {20,10}, {30,10}, {10,10}};
	for (int i = 1;i<20;i++)
	{
		v.push_back(pair<int, int>(i, i));
	}
	vector<promise<int>> prom(v.size());

	ThreadPool myPool;
	for (int i = 0;i<v.size();i++) {
		auto &prom1 = prom[i];
		auto fun = packaged_task<void()>([&v, i, &prom1] {
			prom1.set_value(solveOne(v[i].first, v[i].second));
		});
		myPool.addtask(move(fun));
	}
	myPool.start(4);

	for (auto &v : prom)
	{
		cout << v.get_future().get() << endl;
	}
	myPool.stopme();

	auto timeAfterTask = chrono::system_clock::now();
	chrono::duration<double> diff = timeAfterTask - curTime;
	cout << "Time on task " << diff.count() << endl;

	return 0;
}
#include <iostream>
#include <atomic> // C++11线程库提供的原子类
#include <thread> // C++线程类库的头文件
#include <vector>

using namespace std;

// 原子整形，CAS操作保证给count自增自减的原子操作
std::atomic_int count(0);

// 线程函数
void sumTask()
{
	// 每个线程给count加1000次
	for (int i = 0; i < 1000; ++i)
	{
		count++;
	}
}

int main()
{
	// 创建10个线程放在容器当中
	std::vector<std::thread> vec;
	for (int i = 0; i < 10; ++i)
	{
		vec.push_back(std::thread(sumTask));
	}

	// 等待线程执行完成
	for (int i = 0; i < vec.size(); ++i)
	{
		vec[i].join();
	}

	// 所有子线程运行结束，count的结果每次运行应该都是10000
	std::cout << "count : " << count << std::endl;

	return 0;
}
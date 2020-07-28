#include <iostream>
#include <thread>
#include <mutex>
#include <string>
using namespace std;

// 车票总数是100张
volatile int tickets = 100; 
// 全局的互斥锁
std::mutex mtx;

// 线程函数
void sellTicketTask(std::string wndName)
{
	while (tickets > 0)
	{
		// 获取互斥锁资源
		mtx.lock();
		if (tickets > 0)
		{
			std::cout << wndName << " 售卖第" << tickets << "张票" << std::endl;
			tickets--;
		}
		// 释放互斥锁资源
		mtx.unlock();

		// 每卖出一张票，睡眠100ms，让每个窗口都有机会卖票
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

// 模拟车站窗口卖票，使用C++11 线程互斥锁mutex
int main()
{
	// 创建三个模拟窗口卖票线程
	std::thread t1(sellTicketTask, "车票窗口一");
	std::thread t2(sellTicketTask, "车票窗口二");
	std::thread t3(sellTicketTask, "车票窗口三");

	// 等待三个线程执行完成
	t1.join();
	t2.join();
	t3.join();

	return 0;
}
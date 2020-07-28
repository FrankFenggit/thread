#include <iostream>           // std::cout
#include <thread>             // std::thread
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
#include <vector>

// 锁资源1
std::mutex mtx1;
// 锁资源2
std::mutex mtx2;

// 线程A的函数
void taskA()
{
	// 保证线程A先获取锁1
	std::lock_guard<std::mutex> lockA(mtx1);
	std::cout << "线程A获取锁1" << std::endl;

	// 线程A睡眠2s再获取锁2，保证锁2先被线程B获取，模拟死锁问题的发生
	std::this_thread::sleep_for(std::chrono::seconds(2));

	// 线程A先获取锁2
	std::lock_guard<std::mutex> lockB(mtx2);
	std::cout << "线程A获取锁2" << std::endl;

	std::cout << "线程A释放所有锁资源，结束运行！" << std::endl;
}

// 线程B的函数
void taskB()
{
	// 线程B先睡眠1s保证线程A先获取锁1
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::lock_guard<std::mutex> lockB(mtx2);
	std::cout << "线程B获取锁2" << std::endl;

	// 线程B尝试获取锁1
	std::lock_guard<std::mutex> lockA(mtx1);
	std::cout << "线程B获取锁1" << std::endl;

	std::cout << "线程B释放所有锁资源，结束运行！" << std::endl;
}
int main()
{
	// 创建生产者和消费者线程
	std::thread t1(taskA);
	std::thread t2(taskB);

	// main主线程等待所有子线程执行完
	t1.join();
	t2.join();

	return 0;
}
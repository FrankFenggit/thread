#include <iostream>
#include <thread>
#include <string>
using namespace std;

// 线程1的线程函数
void threadProc1()
{
	cout << "thread-1 run begin!" << endl;
	// 线程1睡眠2秒
	std::this_thread::sleep_for(std::chrono::seconds(2));
	cout << "thread-1 2秒唤醒，run end!" << endl;
}

// 线程2的线程函数
void threadProc2(int val, string info)
{
	cout << "thread-2 run begin!" << endl;
	cout << "thread-2 args[val:" << val << ",info:" << info << "]" << endl;
	// 线程2睡眠4秒
	std::this_thread::sleep_for(std::chrono::seconds(4));
	cout << "thread-2 4秒唤醒，run end!" << endl;
}
int main()
{
	cout << "main thread begin!" << endl;

	// 创建thread线程对象，传入线程函数和参数，线程直接启动运行
	thread t(threadProc1);
	thread t1(threadProc2, 20, "hello world");

	// 等待线程t和t1执行完，main线程再继续运行
	t.join();
	t1.join();

	cout << "main thread end!" << endl;
	return 0;
}

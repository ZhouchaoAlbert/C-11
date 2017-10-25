#ifndef __ATOMICTTEST_H__
#define __ATOMICTTEST_H__
#include <iostream>
#include<windows.h>
#include <thread>
#include <atomic>  
#include"MyLock.h"

std::atomic_llong  sum = { 0LL };

long long sum222 = 0;
CMyLock lk;
void fun()
{
	for (long long i = 0; i < 10000000LL; ++i)
	{
		lk.lock();
		sum222 += i;
		lk.unlock();
	}	
}

//原子数据类型操作
void Test1()
{
	std::cout << "Before joining,sum = " << sum222 << std::endl;
	std::thread t1(fun);
	std::thread t2(fun);
	t1.join();
	t2.join();
	std::cout << "After joining,sum = " << sum222 << std::endl;
}


std::atomic_flag lock = ATOMIC_FLAG_INIT;                               //初始化

void f(int n)
{
	while (lock.test_and_set())                                        //获取锁的状态
		std::cout << "Waiting ... " << std::endl;     //自旋等待
	std::cout << "Thread " << n << " is start working." << std::endl;
}

void g(int n)
{
	Sleep(3);
	std::cout << "Thread " << n << " is going to clear the flag." << std::endl;
	lock.clear();   // 解锁
}

void AtomicTest()
{
	Test1();

	lock.test_and_set();  //设置True
	std::thread t1(f,1);
	std::thread t2(g,2);
	t1.join();
	t2.join();
}

#endif
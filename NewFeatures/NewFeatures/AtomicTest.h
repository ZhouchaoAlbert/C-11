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
		//lk.lock();
		sum += i;
		//lk.unlock();
	}	
}

//ԭ���������Ͳ���
void AtomicTypeTest()
{
	std::cout << "Before joining,sum = " << sum222 << std::endl;
	std::thread t1(fun);
	std::thread t2(fun);
	t1.join();
	t2.join();
	std::cout << "After joining,sum = " << sum222 << std::endl;
}


std::atomic_flag lock = ATOMIC_FLAG_INIT;                    

void f(int n)
{
	while (lock.test_and_set())                       //��ȡ����״̬
		std::cout << "Waiting ... " << std::endl;     //�����ȴ�
	std::cout << "Thread " << n << " is start working." << std::endl;
}

void g(int n)
{
	Sleep(3);
	std::cout << "Thread " << n << " is going to clear the flag." << std::endl;
	lock.clear();   // ����
}

void AtomicTest()
{
	AtomicTypeTest();

	lock.test_and_set();  //����true
	std::thread t1(f,1);
	std::thread t2(g,2);
	t1.join();
	t2.join();
}

#endif
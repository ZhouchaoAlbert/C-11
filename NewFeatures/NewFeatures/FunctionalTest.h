#ifndef __FUNCTIONAL_TEST_H__
#define __FUNCTIONAL_TEST_H__
#include <iostream>
#include<vector>
#include <functional>  
template<typename... Args>

class EventFunction
{
public:
	EventFunction()
	{
	}
	~EventFunction()
	{
	}

	void Bind(std::function<void(Args...)> fun)
	{
		m_vecFun.push_back(fun);
	}

	void Run(Args... args)
	{
		for (auto it : m_vecFun)
		{
			if (!it)
			{
				continue;
			}
			it(args...);
		}
	}
private:
	std::vector<std::function<void(Args...)>>  m_vecFun;
};

class Event
{
public:
	static EventFunction<int, int>* addTest()
	{
		static EventFunction<int, int> add;
		return &add;
	}
	static EventFunction<int, int>* mulTest()
	{
		static EventFunction<int, int> mul;
		return &mul;
	}
	static EventFunction<>* Test()
	{
		static EventFunction<> test;
		return &test;
	}
};

class TestA
{
public:
	void Add()
	{
		Event::addTest()->Bind(std::bind(&TestA::addTest, this, std::placeholders::_1, std::placeholders::_2));
		Event::mulTest()->Bind(std::bind(&TestA::mulTest, this, std::placeholders::_1, std::placeholders::_2));
		int a = 1, b = 8;
		Event::Test()->Bind(std::bind(&TestA::Test, this, a, b));
	}

	void addTest(int a, int b)
	{
		int c = a + b;
		std::cout << "TestA C:" << c << std::endl;
	}
	void mulTest(int a, int b)
	{
		int m = a * b;
		std::cout << "TestA M:" << m << std::endl;
	}
	void Test(int a, int b)
	{
		std::cout << "TestA a :" << a << " b:" <<  b << std::endl;
	}
};

class TestB
{
public:
	void Add()
	{
		Event::addTest()->Bind(std::bind(&TestB::addTest, this, std::placeholders::_1, std::placeholders::_2));
		Event::mulTest()->Bind(std::bind(&TestB::mulTest, this, std::placeholders::_1, std::placeholders::_2));
		int a = 51, b =5 ;
		Event::Test()->Bind(std::bind(&TestB::Test, this, a, b));
	}

	void addTest(int a, int b)
	{
		int c = 2*(a + b);
		std::cout << "TestB C:" << c << std::endl;
	}
	void mulTest(int a, int b)
	{
		int m = 2* (a * b);
		std::cout << "TestB M:" << m << std::endl;
	}
	void Test(int a, int b)
	{
		std::cout << "TestB a :" << a << " b:" << b << std::endl;
	}
};


void FunctionalTest()
{
	TestA ta;
	ta.Add();
	TestB tb;
	tb.Add();
	Event::addTest()->Run(1, 3);
	Event::mulTest()->Run(3, 3);
	Event::Test()->Run();
}


#endif
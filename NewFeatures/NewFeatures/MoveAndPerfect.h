#ifndef __MOVEANDPERFECT_H__
#define __MOVEANDPERFECT_H__
#include<iostream>
using namespace std;

class CHasPtrMem
{
public:
	CHasPtrMem() :m_pData(new int(111))
	{
	}
	CHasPtrMem(const CHasPtrMem & h) : m_pData(new int(*h.m_pData))
	{

	}
	~CHasPtrMem()
	{
		delete m_pData;
	}

	int* m_pData;
};


class CHasPtrMemII
{
public:
	CHasPtrMemII() :m_pData(new int(111))
	{
		std::cout << "Construct:" << ++m_n1 << std::endl;
	}
	CHasPtrMemII(const CHasPtrMemII & h) : m_pData(new int(*h.m_pData))
	{
		std::cout << "Copy Construct:" << ++m_n2 << std::endl;
	}
   //
	CHasPtrMemII(CHasPtrMemII && h) : m_pData(h.m_pData)
	{
		h.m_pData = nullptr;
		std::cout << "Move Construct:" << ++m_n4 << std::endl;
	}
	~CHasPtrMemII()
	{
		std::cout << "Destruct:" << ++m_n3 << std::endl;
		if (m_pData)
		{
			delete m_pData;
			m_pData = NULL;
		}
	}

	int* m_pData;
	static int m_n1;
	static int m_n2;
	static int m_n3;
	static int m_n4;
};

int CHasPtrMemII::m_n1 = 0;
int CHasPtrMemII::m_n2 = 0;
int CHasPtrMemII::m_n3 = 0;
int CHasPtrMemII::m_n4 = 0;
CHasPtrMemII GetTemp()
{
	CHasPtrMemII aa;
	std::cout << "add:" << &aa.m_pData << "aa:" << *aa.m_pData << std::endl;
	return aa;
}

template<class T>
void swap22(T& a, T& b)
{
	T temp(std::move(a));
	a = std::move(b);
	b = std::move(temp);
}

//////////////////////////////
void MoveAndPerfectTest()
{
	//指针成员与拷贝构造
	//CHasPtrMem a;
	//CHasPtrMem b(a);
	//std::cout << "add:" << &a.m_pData << "a:" << *a.m_pData << std::endl;
	//std::cout << "add:" << &b.m_pData << "b:" << *b.m_pData << std::endl;

	CHasPtrMemII a = GetTemp();
	std::cout << "add:" << &a.m_pData << "a:" << *a.m_pData << std::endl;
	//CHasPtrMemII b(a);

	CHasPtrMemII bb;

	CHasPtrMemII cc(std::move(bb));

	std::cout << "add:" << &cc.m_pData << "cc:" << *cc.m_pData << std::endl;
	int aaaa = 1, bbbb = 2;

	swap22(aaaa, bbbb);
}


////////Perfect


void RunCode(int && m)
{
	std::cout << "rvalue ref" << std::endl;
}

void RunCode(int & m)
{ 
	std::cout << "1value ref" << std::endl;
}
void RunCode(const int && m)
{ 
	std::cout << "const rvalue ref" << std::endl;
}

void RunCode(const int & m)
{ 
	std::cout << "const lvalue ref" << std::endl;
}

template <typename T>
void PerfectForward(T &&t)
{
	RunCode(forward<T>(t));
}

void Test() {
	int a;
	int b;
	const int c = 1;
	const int d = 0;
	PerfectForward(a);
	// rvalue ref
	PerfectForward(move(b));
	// const lvalue ref
	PerfectForward(c);
	// const rvalue ref
	PerfectForward(move(a));

}

template <typename T,typename U>
void PerfectForward(T &&t ,U& Func) 
{
	Func(forward<T>(t));
}

void RunCode2(double && m)
{
}

void RunHome2(double && h)
{
}

void RunComp2(double && c) 
{
}

void Test2()
{
	// 1.5
	PerfectForward(1.5, RunComp2);
	//8
	PerfectForward(8, RunCode2);
	// 1.5
	PerfectForward(1.5, RunHome2);
}



#endif
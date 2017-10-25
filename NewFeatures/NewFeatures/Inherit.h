#ifndef __INHERIT_H__
#define __INHERIT_H__

//继承构造
class CBase
{
public:
	CBase(int a) 
	{ 
		m_a = a;
		m_b = 0;
		m_c = 0;
	 }
	CBase(int a, double b)
	{
		m_a = a;
		m_b = b;
		m_c = 0;
	}
	CBase(int a, double b,  char* c) 
	{
		m_a = a;
		m_b = b;
		m_c = c;
	}
private:
	int    m_a;
	double m_b;
	char*  m_c;
};


class CDerived : public CBase
{
public:
	using CBase::CBase;            // 使用CBase中的构造函数

	// Somthing...
	virtual void Test() {  }

private:
	int m_d;
};

//委派构造
class CDeletage
{
public:
	CDeletage() :CDeletage(1)
	{
	}
	CDeletage(int t) : CDeletage(t, 'a')  //委派构造  目标构造
	{
	}
	CDeletage(char n) :CDeletage(1,n)  //委派构造
	{
	}
private:
	CDeletage(int t, char n) :  //目标构造
		m_type(t),
		m_name(n)   
	{
		/*其他初始化*/
	}

private:
	int  m_type;
	char m_name;
};


//委派构造 一个实际应用 
#include<list>
#include<vector>
#include<deque>

class TDConstruted
{
	template<class T> 
	TDConstruted(T first, T last):
		m_l(first,last)
	{
	}
	std::list<int> m_l;

public:
	TDConstruted(std::vector<short>& v) :
		TDConstruted(v.begin(), v.end())
	{

	}
	TDConstruted(std::deque<int>& d) :
		TDConstruted(d.begin(), d.end())
	{

	}
};

#endif
#ifndef __DECLTYPE_TEST_H__
#define __DECLTYPE_TEST_H__
#include <iostream>
#include <typeinfo>

class White {};
class Black {};

void TypeidTest()
{
	White a;
	Black b;
	std::cout << typeid(a).name() << std::endl; // class White
	std::cout << typeid(b).name() << std::endl; // class Black
	White c;
	bool a_b_sametype = (typeid(a).hash_code() == typeid(b).hash_code());
	bool a_c_sametype = (typeid(a).hash_code() == typeid(c).hash_code());
	std::cout << "Same type?" << std::endl;
	std::cout << "A and B  " << (int)a_b_sametype << std::endl; // 0
	std::cout << "A and C  " << (int)a_c_sametype << std::endl; // 1

	int  d;
	float e;
	std::cout << typeid(d).name()  <<"  "  << typeid(e).name()<< std::endl; //
}


//适当扩大模板泛型编程的能力
template<typename T1, typename T2>
void Sum(T1& t1, T2& t2, decltype(t1 + t2)& sum)
{
	s = t1 + t2;
}

template <typename T1, typename T2>
auto compose(T1 t1, T2 t2) -> decltype(t1 + t2)
{
	return t1 + t2;
}

void DecltypeTest() 
{
	std::vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	//decltype 与 typedef使用 
	typedef decltype(vec.begin()) vecType;
	using vecDecltype = decltype(vec);

	using size_tt = decltype(sizeof(0));
	size_tt  stTemp = 1;


	for (vecDecltype::iterator idx = vec.begin(); idx < vec.end(); idx++)
	{
		auto value = idx;
	}
	for (vecType idx = vec.begin(); idx < vec.end(); idx++)
	{
		auto value = idx;
	}

	//重用匿名类型
	enum{ K1, K2, K3 }anony_e;
	union
	{
		decltype(anony_e) key;
		char* name;
	}anony_u;
	struct
	{
		int d;
		decltype(anony_u) id;
	}anony_s[100];

	decltype(anony_s) as;
	as[0].id.key = decltype(anony_e)::K1;


	//适当扩大模板泛型编程的能力
	auto v = compose(2, 3.14);

}



//decltype 推导四规则

int i = 2;
//重载的函数
void Overloaded(int){};
void overloaded(char){};

void DecltypeRuleTest()
{
	int arr[5] = { 0 };
	int *ptr = arr;
	struct S
	{
		double d;
	}s;

	// 规则1: 单个标记符表达式以及访问类成员，推导为本类型
	decltype(arr) varl;              //int[5], 标记符表达式
	decltype(ptr) var2;              //int*    标记符表达式
	decltype(s.d) var3;              //double  成员访问表达式
	//decltype (Overloaded) var4;	 // 无法通过编译，是个重载的函数

	int&& mmmm = 11;
	decltype(mmmm) var5 = 1;	     //将亡值，推导为类型的右值引用

	//规则3:左值，推导为类型的引用
	int i = 7;
	decltype(true ? i : i) var6 = i;  //int& 三元运算操作
	decltype((i)) var7 = i;           //int& 带圆括号的左值
}



#endif
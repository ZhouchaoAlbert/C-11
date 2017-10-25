#ifndef __AUTOTEST_H__
#define __AUTOTEST_H__
#include<iostream>
#include<vector>


class PI {
public:
	double operator *(float v) {
		return (double)val* v;
	}
	const float val = 3.1415927f;
};

template<typename T>
T  AddFunc(T a,T b)
{
	return a + b;
}

void AutoTest()
{
	int a = 1, b = 2;
	auto c = AddFunc(a, b);
	int size = sizeof(c);
	std::cout << "C szie：" << size << std::endl;

	float d = 1.1, e = 2.2;
	auto f = AddFunc(d,e);
	int size2 = sizeof(f);
	std::cout << "F szie：" << size2 << std::endl;

	std::vector<int>vecNum;
	for (int idx = 0; idx < 5; idx++)
	{
		vecNum.push_back(idx);
	}
	for (std::vector<int>::iterator it = vecNum.begin(); it != vecNum.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout  <<	std::endl;
	for (auto it = vecNum.begin(); it != vecNum.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;


	float r = 5.23f;
	PI pi;
	auto s = 2 * (pi * r);
	std::cout << sizeof(s) << std::endl;

	//auto不能解决所有精度问题
	unsigned int aa = 4294967295; // unsigned int 能够存储的最大数据
	unsigned int bb = 1;
	auto cc = aa + bb;
	std::cout << "cc:" << cc << std::endl; // 输出cc为0
}

//用Max2的宏定义效率更高
#define Max1(a, b) ((a) > (b)) ? (a) : (b)
#define Max2(a, b) (	\
					{	\
						auto _a = (a);  \
						auto _b = (b);  \
						(_a > _b) ? _a : _b; \
					}\
					)



//注意：
//auto需要初始化的值进行类型推导，有点类似于引用
//auto不能作为函数参数，否则无法通过编译；
//auto不能推导非静态成员变量的类型，因为auto是在编译时期进行推导；
//auto 不能用于声明数组，否则无法通过编译；
//auto不能作为模板参数(实例化时), 否则无法通过编译。

#endif
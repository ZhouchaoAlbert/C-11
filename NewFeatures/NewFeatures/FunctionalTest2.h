#ifndef __FUNCTIONAL_TEST2_H__
#define __FUNCTIONAL_TEST2_H__
#include<map>
#include <iostream>
#include <functional>
//Function 与 map 结合使用

//普通函数
int add(int i, int j){ return i + j; }

//lambda函数
auto mod = [](int i, int j){return i %j; };

//仿函数
struct div2
{
	int operator() (int i, int j)
	{
		return i / j;
	}
};

void FuntionalTest2()
{
	//灵活的map使用
	std::map<char, std::function<int(int, int)>> mapList =
	{
		{ '+', add },
		{ '-', [](int i, int j){return i - j; } },
		{ '/', div2() },
		{ '%', mod },
	};

	std::cout << "灵活的map测试:"<< std::endl;
	std::cout << "+:" << mapList['+'](11, 5) << std::endl;
	std::cout << "%:" << mapList['%'](11, 5) << std::endl;
	std::cout << "/:" << mapList['/'](11, 5) << std::endl;
	std::cout << "-:" << mapList['-'](11, 5) << std::endl;
}


#endif
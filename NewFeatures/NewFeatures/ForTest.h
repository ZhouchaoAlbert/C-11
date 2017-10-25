#ifndef __FORTEST_H__
#define __FORTEST_H__
#include <iostream>
#include <algorithm>

//for_each的模板函数，其内含指针的自增。


void action1(int &e)
{ 
	e *= 2; 
}
void action2(int &e)
{ 
	std::cout << e << "\t";
}
void  ForEachTest() 
{
	int arr[5] = { 1, 2, 3, 4, 5 };
	std::for_each(arr, arr + sizeof(arr) / sizeof(arr[0]), action1);
	std::for_each(arr, arr + sizeof(arr) / sizeof(arr[0]), action2);

	int a[5] = { 1, 2, 3, 4, 5 };
	for (int& e : a)
		e *= 2;
	for (int& e : a)
		std::cout << e << "\t";
	// or(1)
	for (int e : a)
		std::cout << e << "\t";
	// or(2)
	for (auto e : a)
		std::cout << e << "\t";
	int s = 0;
	for (auto e : a)
		s += e;
	std::cout << s << "\t";
}


#endif
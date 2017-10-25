#ifndef __LAMBDATEST_H__
#define __LAMBDATEST_H__
#include<vector>
#include <iostream>
#include <algorithm>
using namespace std;


class CLabmdaTest
{
public:
	void func(int x, int y){
		//auto m1 = []  { return m_i; };                         
		auto m2 = [=] { return m_i + x + y; };               
		auto m3 = [&] { return m_i + x + y; };               
		auto m4 = [this] { return m_i; };                        
		//auto m5 = [this] { return m_i + x + y; };           
		auto m6 = [this, x, y] { return m_i + x + y; };       
		auto m7 = [this] { return m_i++; };                   
	}
private:
	int m_i{ 0 };
};

void Function()
{
	int m = 0, n = 1;
	//auto f1 = [] { return m; };                            
	auto f2 = [&] { return m++; };                      
	auto f3 = [=] { return m; };                         
	//auto f4 = [=] {return m++; };                       
	//auto f5 = [m] { return m + n; };                  
	auto f6 = [m, &n] { return m + (n++); };        
	auto f7 = [=, &n] { return m + (n++); };        
}


void LambdaTest()
{
	
	auto Min = [](int a, int b)->int{ 
		return (a <= b ? (a) : (b));
	};
	int min = Min(3, 5); 
	std::cout << "min:" << min  << std::endl;
	
	std::vector<int> vecList{ 1, 2, 3, 4, 5 ,6, 7, 8, 9, 10};

	int count = std::count_if(vecList.begin(), vecList.end(), [](int x){ return x > 5 && x<10; });

	int total = 0;
	std::for_each(vecList.begin(), vecList.end(), [&total](int x) {
	    total += x;
	});
	std::cout << "total:" << total << std::endl;

	int x = 6;
	vecList.erase(std::remove_if(vecList.begin(), vecList.end(), [x](int n) { return n < x; }), vecList.end());

	std::cout << "vecList: ";
	std::for_each(vecList.begin(), vecList.end(), [](int x){
		std::cout << x << ' ';
	});
	std::cout << std::endl;

	int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::sort(arr, &arr[10], [](int x, int y){ return x > y; });
}





#endif 
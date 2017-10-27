#ifndef __AUTOTEST_H__
#define __AUTOTEST_H__
#include<iostream>
#include<vector>
#include<map>
#include <string>

//用Max2的宏定义效率更高
#define Max1(a, b) ((a) > (b)) ? (a) : (b)
#define Max2(a, b) (	\
					{	\
					auto _a = (a);  \
					auto _b = (b);  \
					(_a > _b) ? _a : _b; \
					}\
					)

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
	int aa = 1, bb = 2;
	auto cc = AddFunc(aa, bb);
	int size = sizeof(cc);
	std::cout << "C szie：" << size << std::endl;

	float dd = 1.1, ee = 2.2;
	auto ff = AddFunc(dd, ee);
	int size2 = sizeof(ff);
	std::cout << "F szie：" << size2 << std::endl;

	float r = 5.23f;
	PI pi;
	auto s = 2 * (pi * r);
	std::cout << sizeof(s) << std::endl;

	//vector
	std::vector<std::string> c;
	c.push_back("1111");
	c.push_back("2222");
	std::cout << "c: ";
	for (auto idx : c)
	{
		std::cout << idx << " ";
	}
	std::cout << std::endl;

	//map
	std::map<std::string, int> map;
	map["1111"] = 1111;
	map["2222"] = 2222;
	map["3333"] = 3333;
	std::cout << "map: ";
	auto it = map.find("222");
	for (auto it = begin(map); it != end(map); ++it)
	{
		std::cout << it->first << " " << it->second << " ";
	}
	std::cout << std::endl;

	//map-vector
	std::map<std::string, std::vector<int>> map2;
	std::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	map2["one"] = v;

	for (auto it2 = begin(map2); it2 != end(map2); ++it2)
	{
		std::cout << it2->first << std::endl;
		for (auto v : it2->second)
		{
			std::cout << v << std::endl;
		}
	}
	std::cout << std::endl;


	//map-map
	std::map<std::string, std::map<int, std::string>>map3;
	map3["1"][11] = "111";
	map3["2"][22] = "222";
	map3["3"][33] = "333";
	map3["4"][44] = "444";
	for (auto it4 = begin(map3); it4 != end(map3); it4++)
	{
		std::cout << it4->first << std::endl;
		for (auto it5 = begin(it4->second); it5 != end(it4->second); it5++)
		{
			std::cout << it5->first << " " << it5->second << std::endl;
		}
	}
	std::cout << std::endl;
}



#endif
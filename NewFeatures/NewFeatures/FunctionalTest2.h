#ifndef __FUNCTIONAL_TEST2_H__
#define __FUNCTIONAL_TEST2_H__
#include<map>
#include <iostream>
#include <functional>
//Function �� map ���ʹ��

//��ͨ����
int add(int i, int j){ return i + j; }

//lambda����
auto mod = [](int i, int j){return i %j; };

//�º���
struct div2
{
	int operator() (int i, int j)
	{
		return i / j;
	}
};

void FuntionalTest2()
{
	//����mapʹ��
	std::map<char, std::function<int(int, int)>> mapList =
	{
		{ '+', add },
		{ '-', [](int i, int j){return i - j; } },
		{ '/', div2() },
		{ '%', mod },
	};

	std::cout << "����map����:"<< std::endl;
	std::cout << "+:" << mapList['+'](11, 5) << std::endl;
	std::cout << "%:" << mapList['%'](11, 5) << std::endl;
	std::cout << "/:" << mapList['/'](11, 5) << std::endl;
	std::cout << "-:" << mapList['-'](11, 5) << std::endl;
}


#endif
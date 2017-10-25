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
	std::cout << "C szie��" << size << std::endl;

	float d = 1.1, e = 2.2;
	auto f = AddFunc(d,e);
	int size2 = sizeof(f);
	std::cout << "F szie��" << size2 << std::endl;

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

	//auto���ܽ�����о�������
	unsigned int aa = 4294967295; // unsigned int �ܹ��洢���������
	unsigned int bb = 1;
	auto cc = aa + bb;
	std::cout << "cc:" << cc << std::endl; // ���ccΪ0
}

//��Max2�ĺ궨��Ч�ʸ���
#define Max1(a, b) ((a) > (b)) ? (a) : (b)
#define Max2(a, b) (	\
					{	\
						auto _a = (a);  \
						auto _b = (b);  \
						(_a > _b) ? _a : _b; \
					}\
					)



//ע�⣺
//auto��Ҫ��ʼ����ֵ���������Ƶ����е�����������
//auto������Ϊ���������������޷�ͨ�����룻
//auto�����Ƶ��Ǿ�̬��Ա���������ͣ���Ϊauto���ڱ���ʱ�ڽ����Ƶ���
//auto ���������������飬�����޷�ͨ�����룻
//auto������Ϊģ�����(ʵ����ʱ), �����޷�ͨ�����롣

#endif
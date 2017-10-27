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


//�ʵ�����ģ�巺�ͱ�̵�����
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
	//decltype �� typedefʹ�� 
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

	//������������
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


	//�ʵ�����ģ�巺�ͱ�̵�����
	auto v = compose(2, 3.14);

}



//decltype �Ƶ��Ĺ���

int i = 2;
//���صĺ���
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

	// ����1: ������Ƿ����ʽ�Լ��������Ա���Ƶ�Ϊ������
	decltype(arr) varl;              //int[5], ��Ƿ����ʽ
	decltype(ptr) var2;              //int*    ��Ƿ����ʽ
	decltype(s.d) var3;              //double  ��Ա���ʱ��ʽ
	//decltype (Overloaded) var4;	 // �޷�ͨ�����룬�Ǹ����صĺ���

	int&& mmmm = 11;
	decltype(mmmm) var5 = 1;	     //����ֵ���Ƶ�Ϊ���͵���ֵ����

	//����3:��ֵ���Ƶ�Ϊ���͵�����
	int i = 7;
	decltype(true ? i : i) var6 = i;  //int& ��Ԫ�������
	decltype((i)) var7 = i;           //int& ��Բ���ŵ���ֵ
}



#endif
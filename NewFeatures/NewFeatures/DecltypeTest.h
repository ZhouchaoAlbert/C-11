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
//RTTI�޷��������Ա������
//��ΪRTTI������ʱ��ȷ�������ͣ���������������ڱ���ʱȷ�����͡�
//���ң� 

using size_t    = decltype(sizeof(0));
using ptrdiff_t = decltype((int *)0 - (int*)0);
using nullptr_t = decltype(nullptr);

const int&& foo(); 
const int bar(); 
int i;
struct A { double x; };// ͨ���ĳ�����Ҫʹ���Ƶ��������������Ͷ����ǵ�����ʶ����

auto add(int q, int p)->int
{
	return q + p;
}

//decltype ����˵��������ָ�����ʽ�����͡��ڴ˹����У��������������ʽ���õ��������ͣ�ȴ��ʵ�ʼ�����ʽ��ֵ��
void DecltypeTest() 
{
	int c = add(1, 2);
	nullptr_t t = nullptr;
	std::cout << "t:" << "  " << sizeof(t) << std::endl;
  
	const double& mmm = 6;
	const A* a = new A();
	decltype(foo()) x1 = 0;		// ����Ϊconst int&&
	decltype(bar()) x2 = 0;		// ����Ϊint
	decltype(i) x3;				// ����Ϊint
	decltype(a->x) x4;			// ����Ϊdouble
	decltype((a->x)) x5 = mmm;	// ����Ϊconst double&

}


void DecltypeRuleTest()
{
	int i = 2;
	int arr[5] = { 0 };
	int *ptr = arr;
	struct S 
	{
		double d;
	} s;
	void overload(int);
	void overload(char);
	int&& RvalRef();
	const bool Func(int);

	// ����1
	decltype(arr) var1; // int [5]
	decltype(ptr) var2; // int*
	decltype(s.d) var4; // double
	//decltype(overload) var5; // wrong

	// ����2
	decltype(RvalRef()) val6 = 1; // int&&

	// ����3
	decltype(true ? i : i) var7 = i; // int&
	decltype((i)) var8 = i; // int&
	decltype(++i) var9 = i; // int&
	decltype(arr[3]) var10   = i; // int&
	decltype(*ptr) var11    = i; //int&
	decltype("lval") var3 = "lval"; // (const char*)&

	// ����4
	decltype(1) var13;        // int
	decltype(i++) var14;      // int
	decltype(Func(1)) var15;  // const bool

}



#endif
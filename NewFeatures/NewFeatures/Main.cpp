// NewFeatures.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "AutoTest.h"
#include"DecltypeTest.h"
#include"ForTest.h"

#include "MemInitTest.h"
#include"Inherit.h"
#include"MoveAndPerfect.h"

#include"PointerTest.h"
#include"AtomicTest.h"
#include"LambdaTest.h"
#include "Buffer.h"


int _tmain(int argc, _TCHAR* argv[])
{
	AutoTest();
	TypeidTest();
	DecltypeTest();
	DecltypeRuleTest();
	ForEachTest();
	MemInitTest();

	MoveAndPerfectTest();

	PointerTest();
	AtomicTest();
	LambdaTest();

	CBuffer<char> b1("buftest", 64);
	char arr[10]  = "12345679";
	b1.Append(arr, sizeof(arr));
	char* buf = b1.GetBuf();
	int len   = b1.GetLen();
	std::string str(buf);

	//移动构造
	CBuffer<char> b2 = GetBuffer<char>("bufTest2");
	char arr2[10] = "qazwsxedc";
	b2.Append(arr2, sizeof(arr2));
	char* buf2 = b2.GetBuf();
	int   len2 = b2.GetLen();
	std::string str2(buf2);
	
	
	getchar();
	return 0;
}

#include "smart_ptr.h"

struct MyStruct
{
public:
	MyStruct(){}
	MyStruct(int a, int b) :a(a), b(b) {}
	int a;
	int b;
};

int main2()
{
	MyStruct *s = new MyStruct();
	s->a = 10;
	s->b = 20;

	smart_ptr<MyStruct> sp(s);

	cout << sp->a   << endl;
	cout << sp->b   << endl;
	cout << (*sp).a << endl;

	smart_ptr<MyStruct> sp3 = sp;

	smart_ptr<MyStruct> sp2 = make_smart<MyStruct>(100, 200);
 	cout << sp2->a << endl;
 	cout << sp2->b << endl;
 
 	auto p = sp2.release();
 	cout << p->a << endl;
 	cout << p->b << endl;
 	delete p;

	getchar();
 	return 0;
}
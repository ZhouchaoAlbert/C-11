#ifndef __MEMINITTEST_H__
#define __MEMINITTEST_H__
//1
class CInit
{
public:
	int GetA()
	{
		return a;
	}
	double GetB()
	{
		return b;
	}
	float GetC()
	{
		return c;
	}
private:
	int    a = 3;
	double b{ 1.22 };
	float  c = 4;
	char*  p{ nullptr };
};

struct CMem {
public:
	CMem() 
	{
		std::cout << "Mem default, num: " << num << std::endl; 
	}
	CMem(int i) : num(i)
	{
		std::cout << "Mem, num: " << num << std::endl;
	}

public:
	int num = 2;  // 使用=初始化非静态成员
};

class CObject {
public:
	CObject()
	{
		std::cout << "Object default. val: " << val << std::endl;
	}
	CObject(int i) : val('G'), a(i) 
	{
		std::cout << "Object. val: " << val << std::endl; 
	}
	void NumOfA()
	{
		std::cout << "number of A: " << a.num << std::endl;
	}
	void NumOfB()
	{ 
		std::cout << "number of B: " << b.num << std::endl;
	}

private:
	char val{ 'g' };   // 使用{}初始化非静态成员
	CMem a;
	CMem b{ 19 };      // 使用{}初始化非静态成员
};

void MemInitTest()
{

	CInit  init;
	int    a = init.GetA();
	double b = init.GetB();
	float  c = init.GetC();

	CMem member;         // Mem default, num: 2
	CObject obj;         
	// Mem default, num: 2
	// Mem, num: 19
	// Object default. val: g

	obj.NumOfA();     // number of A: 2
	obj.NumOfB();     // number of B: 19

	CObject obj2(7);    
	// Mem, num: 7
	// Mem, num: 19
	// Group. val: G

	obj2.NumOfA();    // number of A: 7
	obj2.NumOfB();    // number of B: 19
}

#endif
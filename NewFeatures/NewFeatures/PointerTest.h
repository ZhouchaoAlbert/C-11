#ifndef __POINTER_H__
#define __POINTER_H__
#include<iostream>
#include<string>
#include<memory>
#include<assert.h>
using namespace std;

class CReport
{
public:
	CReport(const string s) :str(s) 
	{
		cout << "object created!" << endl;
	}
	~CReport() 
	{ 
		cout << "object deleted!" << endl;
	}
	void comment(string owner) const 
	{ 
		cout << owner << str << endl;
	}

private:
	string str;
};


void AutoPtrTest()
{
	auto_ptr<CReport> ps(new CReport("using auto_ptr."));
	ps->comment(string("ps:"));

	auto_ptr<CReport> p1;
	//��ֵ��Psʧȥ�˶��ڴ���������Ȩ��������ʹ��
	p1 = ps;  
	p1->comment(string("p1:"));

	//ps->comment(string("after p1=ps"));  //err
}


class CShared
{
public:
	CShared(shared_ptr<int> sp) :m_sp(sp)
	{ 
	}
	void Print() { cout << "count:" << m_sp.use_count() << "v=" << *m_sp << endl; }
private:
	shared_ptr<int> m_sp;
};

void sp_print_func(shared_ptr<int> sp)
{
	cout << "count:" << sp.use_count() << "v =" << *sp << endl;
}

void ShareProTest()
{
	shared_ptr<int> sp(new int(100));

	CShared sp1(sp), sp2(sp);
	sp1.Print();
	sp2.Print();

	*sp = 20;
	sp_print_func(sp);

	sp1.Print();
}

//share_ptr
void SharePtrTest()
{
	shared_ptr<int> spi(new int); 
	assert(spi); 
	assert(spi.unique()); //shared_ptr��ָ���Ψһ������
	*spi = 250;  
	
	//����һ����(NULL)������ָ��
	shared_ptr<int> spa;  
	//������һ��shared_ptr���ָ��Ĺ���Ȩ��ͬʱ���ü�����1�����������shared_ptr����һ��ָ��Ĺ���Ȩ��
	 spa = spi;
	 assert(spa == spi && spa.use_count() == 2);
	 
	 *spa = 100;
	 assert(*spi == 100);

	 spa.reset();

	 assert(spi);

	shared_ptr<string> sps(new string("helloworld"));  
	assert(sps->size() == 10);  

	auto_ptr<CReport> api(new CReport("using auto_ptr."));
	//shared_ptr<CReport> spai(api.get());
	//api->comment(string("p3:"));

	ShareProTest();
}



unique_ptr<CReport> GetReportObj(const char *s)
{
	unique_ptr<CReport> tObj(new CReport(s));
	return tObj;
}

//unique_ptr
void UniquePtrTest()
{
	unique_ptr<CReport> ps;
	ps = GetReportObj("Unique pointer");
	ps->comment(string("un_ptr:"));

	unique_ptr<string> pu1(new string("hello world"));
	unique_ptr<string> pu2;
	//pu2 = pu1;    //#err

	unique_ptr<CReport> ps1, ps2;
	ps1 = GetReportObj(" U_P");
	ps2 = std::move(ps1);  
	ps1 = GetReportObj(" and more");
	ps2->comment("up_p2");
	ps1->comment("up_p1");

	std::unique_ptr<double[]> parr(new double[5]);
}


void PointerTest()
{
	AutoPtrTest();
	SharePtrTest();
	UniquePtrTest();
}

#endif
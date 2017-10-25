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

int _tmain(int argc, _TCHAR* argv[])
{
	AutoTest();
	DecltypeTest();
	ForEachTest();
	MemInitTest();

	MoveAndPerfectTest();

	PointerTest();
	AtomicTest();
	LambdaTest();
	getchar();
	return 0;
}

/*


#include <algorithm>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;
struct Plus {
template <typename T, typename U>
auto operator()(T&& t, U&& u) const
-> decltype(forward<T>(t) + forward<U>(u)) {
return forward<T>(t) + forward<U>(u);
}
};
int main() {
vector<int> i;
i.push_back(1);
i.push_back(2);
i.push_back(3);
vector<int> j;
j.push_back(40);
j.push_back(50);
j.push_back(60);
vector<int> k;
vector<string> s;
s.push_back("cut");
s.push_back("flu");
s.push_back("kit");
vector<string> t;
t.push_back("e");
t.push_back("ffy");
t.push_back("tens");
vector<string> u;
transform(i.begin(), i.end(), j.begin(), back_inserter(k), Plus());
transform(s.begin(), s.end(), t.begin(), back_inserter(u), Plus());
for_each(k.begin(), k.end(), [](int n) { cout << n << " "; });
cout << endl;
for_each(u.begin(), u.end(), [](const string& r) { cout << r << " "; });
cout << endl;
}
*/
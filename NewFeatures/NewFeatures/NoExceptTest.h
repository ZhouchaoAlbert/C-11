#ifndef __NOEXPECTTEST_H__
#define __NOEXPECTTEST_H__
#include <iostream>
using namespace std;
void Throw() 
{
	throw 1;
}

void NoBlockThrow()
{ 
	Throw();
}

void BlockThrow() noexcept
{ 
	Throw();
}

int NoExceptTest() 
{
	try {
		Throw();
	}
	catch (...) {
		cout << "Found throw." << endl;     // Found throw.
	}

	try {
		NoBlockThrow();
	}
	catch (...) {
		cout << "Throw is not blocked." << endl;    // Throw is not blocked.
	}

	try {
		BlockThrow();   // terminate called after throwing an instance of 'int'
	}
	catch (...) {
		cout << "Found throw 1." << endl;
	}
}
#endif 
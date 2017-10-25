#ifndef __MYLOCK_H_
#define __MYLOCK_H_
#include <iostream>
#include <atomic>
#include <thread>

class CMyLock
{
public:
	CMyLock();
	void lock();
	void unlock();
private:
	std::atomic_flag m_flag;
};



CMyLock::CMyLock()
{
	m_flag.clear();                   
}

void CMyLock::lock()
{
	while (m_flag.test_and_set())
		;
}

void CMyLock::unlock()
{
	m_flag.clear();
}

#endif
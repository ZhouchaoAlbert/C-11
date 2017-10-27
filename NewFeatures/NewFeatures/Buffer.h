#ifndef __BUFFER_H__
#define __BUFFER_H__
#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>

template <typename T>
class CBuffer
{
public:
	CBuffer() :
		m_size(128),
		m_buffer(new T[128])
	{
	}

	CBuffer(const std::string& name, size_t size) :
		m_name(name),
		m_size(size),
		m_buffer(new T[size])
	{
	}


	CBuffer(const CBuffer& copy) :
		m_name(copy.m_name),
		m_size(copy.m_size),
		m_buffer(new T[copy.m_size])
	{
		T* source = copy.m_buffer.get();
		T* dest   = m_buffer.get();
		std::copy(source, source + copy.m_size, dest);
	}

	CBuffer& operator=(const CBuffer& copy)
	{
		if (this != copy)
		{
			m_name = copy.m_name;
			if (m_size != copy.m_size)
			{
				m_buffer = nullptr;
				m_size   = copy.m_size;
				m_buffer = m_size > 0 > new T[m_size] : nullptr;
			}

			T* source = copy.m_buffer.get();
			T* dest = m_buffer.get();
			std::copy(source, source + copy.m_size, dest);
		}
		return *this;
	}

	//移动构造
	CBuffer(CBuffer&& temp) :
		m_name(std::move(temp.m_name)),
		m_size(temp.m_size),
		m_buffer(std::move(temp.m_buffer))
	{
		temp.m_buffer = nullptr;
		temp.m_size = 0;
	}

	//移动赋值构造
	CBuffer& operator=(CBuffer&& temp)
	{
		assert(this != &temp); 

		m_buffer = nullptr;
		m_size   = temp.m_size;
		m_buffer = std::move(temp.m_buffer);
		m_name   = std::move(temp.m_name);

		temp.m_buffer = nullptr;
		temp.m_size = 0;
		return *this;
	}
	INT32 Append(T *szbuf, UINT32 udatelen)
	{
		if (szbuf && udatelen > 0)
		{
			if ((udatelen + m_datalen) > m_size)
			{
				std::unique_ptr<T[]> newbuf(new T[udatelen + m_datalen + m_size]);
				if (NULL == newbuf)
				{
					return -1;
				}
				memcpy(newbuf.get(),m_buffer.get(), udatelen + m_datalen + m_size);

				m_buffer = std::move(newbuf);
				m_size   = udatelen + m_datalen + m_size;
			}
			memcpy(m_buffer.get() + m_datalen, szbuf, udatelen);
			m_datalen += udatelen;
			return 0;
		}
		return -1;
	}

	T* GetBuf()
	{
		return m_buffer.get();
	}

	UINT32 GetLen()
	{
		return m_datalen;
	}
private:
	std::string				m_name;
	size_t					m_size;
	size_t					m_datalen;
	std::unique_ptr<T[]>	m_buffer;
};

template <typename T>
CBuffer<T> GetBuffer(const std::string& name)
{
	CBuffer<T> b(name, 128);
	return b;
}
#endif
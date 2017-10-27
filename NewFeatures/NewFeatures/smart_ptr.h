#ifndef  __SMART_PTR_H__
#define  __SMART_PTR_H__
#include <functional>

//实现一个智能指针
template <typename T>
class smart_ptr
{
public:
	smart_ptr();
	~smart_ptr();
	explicit smart_ptr(T*);
	smart_ptr(const smart_ptr&);
	smart_ptr(T*, std::function<void(T*)>);
	smart_ptr& operator=(const smart_ptr&);
	T& operator*() const;
	T* operator->() const;

	explicit operator bool() const;//向bool的类型转换

	bool unique();
	void reset();
	void reset(T*);
	void reset(T*, std::function<void(T*)>);
	T*   release();
	T*   get() const;

private:
	// 默认的deleter
	static std::function<void(T*)> default_del;

private:
	unsigned* m_p_use_count = nullptr;
	T* m_pobject            = nullptr;
	std::function<void(T*)> m_del = default_del;
};

template <typename T>
std::function<void(T*)> smart_ptr<T>::default_del = [](T*p) {delete p; p = nullptr; };


template <typename T, typename... Args>
smart_ptr<T> make_smart(Args&&... args)
{
	smart_ptr<T> sp(new T(std::forward<Args>(args)...));
	return sp;
}


template <typename T>
smart_ptr<T>::smart_ptr()
:m_pobject(nullptr), m_p_use_count(new unsigned(1))
{
}


template <typename T>
smart_ptr<T>::smart_ptr(T *p)
:m_pobject(p), m_p_use_count(new unsigned(1))
{
}


template <typename T>
smart_ptr<T>::smart_ptr(T *p, std::function<void(T*)> del)
:m_pobject(p), m_p_use_count(new unsigned(1)), m_del(del)
{
}


template <typename T>
smart_ptr<T>::smart_ptr(const smart_ptr& rhs)
:m_pobject(rhs.m_pobject), m_p_use_count(rhs.m_p_use_count), m_del(rhs.m_del)
{
	(*m_p_use_count)++;
}


template <typename T>
smart_ptr<T>& smart_ptr<T>::operator =(const smart_ptr &rhs)
{
	m_del = rhs.m_del;         //使用rhs的deleter

	++(*rhs.m_p_use_count);	   //递增右侧运算对象的引用计数

	if (--(*m_p_use_count) == 0)//递减本对象的引用计数
	{
		// 如果管理的对象没有其他用户了，则释放对象分配的成员
		m_del(m_pobject);
		delete m_p_use_count;
	}

	m_p_use_count = rhs.m_p_use_count;
	m_pobject = rhs.m_pobject;

	return *this; // 返回本对象
}


template <typename T>
T& smart_ptr<T>::operator*() const
{
	return *m_pobject;
}


template <typename T>
T* smart_ptr<T>::operator->() const
{
	return &this->operator*();
}


template <typename T>
smart_ptr<T>::~smart_ptr()
{
	if (--(*m_p_use_count) == 0)
	{
		m_del(m_pobject);
		m_pobject = nullptr;

		delete m_p_use_count;
		m_p_use_count = nullptr;
	}
}


template <typename T>
bool smart_ptr<T>::unique()
{
	return *m_p_use_count == 1;
}


template <typename T>
void smart_ptr<T>::reset()
{
	(*m_p_use_count)--;

	if (*m_p_use_count == 0)
	{
		m_del(m_pobject);
	}

	m_pobject = nullptr;
	*m_p_use_count = 1;
	m_del = default_del;
}


template <typename T>
void smart_ptr<T>::reset(T* p)
{
	(*m_p_use_count)--;

	if (*m_p_use_count == 0)
	{
		m_del(m_pobject);
	}

	m_pobject = p;
	*m_p_use_count = 1;
	m_del = default_del;
}


template <typename T>
void smart_ptr<T>::reset(T *p, std::function<void(T*)> del)
{
	reset(p);
	m_del = del;
}


template <typename T>
T* smart_ptr<T>::release()
{
	(*m_p_use_count)--;

	if (*m_p_use_count == 0)
	{
		*m_p_use_count = 1;
	}

	auto p = m_pobject;
	m_pobject = nullptr;

	return p;
}


template <typename T>
T* smart_ptr<T>::get() const
{
	return m_pobject;
}


template <typename T>
smart_ptr<T>::operator bool() const
{
	return m_pobject != nullptr;
}


























#if  0
// 模仿shared_ptr实现一个智能指针
template <typename T>
class smart_ptr
{
public:
	smart_ptr():m_pobj(nullptr), m_p_use_count(new unsigned(1))
	{
	}

	~smart_ptr()
	{
		if (0 == --(*m_p_use_count))
		{
			m_del(m_pobj);
			m_pobj = nullptr;

			delete m_p_use_count;
			m_p_use_count = nullptr;
		}
	}

	explicit smart_ptr(T*) :m_pobj(p), m_p_use_count(new unsigned(1))
	{
	}

	smart_ptr(const smart_ptr& rhs) :m_pobj(rhs.m_pobj), m_p_use_count(rhs.m_p_use_count), m_del(rhs.m_del)
	{
		(*m_p_use_count)++;
	}

	T& operator*() const
	{
		return *m_pobj;
	}

	T* operator->() const
	{
		return &this->operator*();
	}

	explicit operator bool() const	// 向bool的类型转换
	{
		return m_pobj != nullptr;
	}

	smart_ptr<T>& smart_ptr<T>::operator =(const smart_ptr &rhs)
	{
		m_del = rhs.m_del;//使用rhs的deleter

		++(*rhs.m_p_use_count);		//递增右侧运算对象的引用计数
		
		if (--(*m_p_use_count) == 0)//递减本对象的引用计数
		{
			// 如果管理的对象没有其他用户了，则释放对象分配的成员
			m_del(m_pobj);
			m_pobj = nullptr;
			delete m_p_use_count;
			m_p_use_count = nullptr;
		}

		m_p_use_count = rhs.m_p_use_count;
		m_pobj = rhs.m_pobj;
		return *this; // 返回本对象
	}

	smart_ptr(T *p, std::function<void(T*)> del):m_pobj(p), m_p_use_count(new unsigned(1)), m_del(del)
	{
	}

	bool unique()
	{
		return *m_p_use_count == 1;
	}

	void reset()
	{
		(*m_p_use_count)--;
		if (*m_p_use_count == 0)
		{
			m_del(m_pobj);
		}

		m_pobj = nullptr;
		*m_p_use_count = 1;
		m_del = default_del;
	}

	void reset(T* p)
	{
		(*m_p_use_count)--;
		if (*m_p_use_count == 0)
		{
			m_del(m_pobj);
		}

		m_pobj = p;
		*m_p_use_count = 1;
		m_del = default_del;
	}

	void smart_ptr<T>::reset(T *p, std::function<void(T*)> del)
	{
		reset(p);
		m_del = del;
	}


	T* release()
	{
		(*m_p_use_count)--;
		if (*m_p_use_count == 0)
		{
			*m_p_use_count = 1;
		}
		auto p = m_pobj;
		m_pobj = nullptr;
		return p;
	}


	T* get() const
	{
		return m_pobj;
	}

private:
	// 默认的deleter
	static std::function<void(T*)> default_del;

private:
	unsigned* m_p_use_count{ nullptr };
	T*        m_pobj{ nullptr };
	std::function<void(T*)> m_del = default_del;
};


template <typename T>
std::function<void(T*)> smart_ptr<T>::default_del = [](T*p) {delete p; p = nullptr; };


template <typename T, typename... Args>
smart_ptr<T> make_smart(Args&&... args)
{
	smart_ptr<T> sp(new T(std::forward<Args>(args)...));
	return sp;
}


#endif

#endif
#pragma once
#include "CObject.h"

class MyShared_ptr
{
	struct Control {
		long counter;
	};

public:
	//Constructors, assignment operators, destructor
	MyShared_ptr() noexcept;
	explicit MyShared_ptr(CObject* ptr);
	MyShared_ptr(const MyShared_ptr& r) noexcept;
	MyShared_ptr(MyShared_ptr&& r) noexcept;

	MyShared_ptr& operator=(const MyShared_ptr& r) noexcept;
	MyShared_ptr& operator=(MyShared_ptr&& r) noexcept;

	~MyShared_ptr();

	//Modifiers
	void reset(CObject* ptr = nullptr);
	void swap(MyShared_ptr& r) noexcept;

	//Observers
	CObject* get() const noexcept;
	CObject& operator*() const;
	CObject* operator->() const noexcept;
	long use_count() const noexcept;
	explicit operator bool() const noexcept;
private:
	void destruct();

	CObject* m_Data;
	Control* m_Control;
};


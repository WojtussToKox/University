#pragma once
#include "ReferenceCounter.h"

template<typename T>
class MySmartPointer
{
public:
	MySmartPointer(T* pPointer)
	{
		pointer = pPointer;
		counter = new ReferenceCounter();
		counter->addReference();
	}

	MySmartPointer(const MySmartPointer& pOther)
	{
		pointer = pOther.pointer;
		counter = pOther.counter;
		counter->addReference();
	}

	~MySmartPointer()
	{
		if (counter->decreaseReference() == 0)
		{
			delete pointer;
			delete counter;
		}
	}

	T& operator*() { return(*pointer); }
	T* operator->() { return(pointer); }
	MySmartPointer<T>& operator= (const MySmartPointer<T>& pOther);

private:
	ReferenceCounter* counter;
	T* pointer;
};

template<typename T>
inline MySmartPointer<T>& MySmartPointer<T>::operator= (const MySmartPointer<T>& pOther)
{
	if (this == &pOther) {
		return *this;
	}

	if (counter->decreaseReference() == 0)
	{
		delete pointer;
		delete counter;
	}

	pointer = pOther.pointer;
	counter = pOther.counter;
	counter->addReference();

	return *this;
}

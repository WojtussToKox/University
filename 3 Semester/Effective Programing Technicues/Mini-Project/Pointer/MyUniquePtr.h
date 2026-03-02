#pragma once

#include <utility> // dla std::move

template <typename T>
class MyUniquePtr {

public:

	MyUniquePtr() : ptr(nullptr) {}
	
	explicit MyUniquePtr(T* p) : ptr(p) {}
	
	~MyUniquePtr() {
		delete ptr;
	}

	// Blokada kopiowania (wymóg unikalnoœci)
	MyUniquePtr(const MyUniquePtr&) = delete;
	MyUniquePtr& operator=(const MyUniquePtr&) = delete;


	// Przenoszenie (Move Semantics)
	MyUniquePtr(MyUniquePtr&& other) : ptr(other.ptr) {
		other.ptr = nullptr;
	}
	MyUniquePtr& operator=(MyUniquePtr&& other) {
		if (this != &other) {
			delete ptr;
			ptr = other.ptr;
			other.ptr = nullptr;
		}

		return *this;
	}

	T& operator*() const { return *ptr; }
	T* operator->() const { return ptr; }
	T* get() const { return ptr; }

	void reset(T* new_ptr = nullptr) {
		if (ptr != new_ptr) {
			delete ptr;
			ptr = new_ptr;
		}
	}

	T* release() {
		T* temp = ptr;
		ptr = nullptr;
		return temp;
	}

private:
	T* ptr;
};
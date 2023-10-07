#pragma once
#include<string>
using namespace std;

template<class T>
class my_unique_pointer {
private:
	T* _ptr;
	int _size{};
public:
	my_unique_pointer()
	{
		cout << "Constructor with no parameter runs\n";
		this->_ptr = nullptr;
		this->_size = 0;
	}
	my_unique_pointer(int size)
	{
		cout << "Constructor to make array runs\n";
		this->_ptr = new T[size];
		this->_size = size;
	}
	my_unique_pointer(const my_unique_pointer<T>& p) = delete;
	my_unique_pointer operator=(const my_unique_pointer<T>& p) = delete;
	my_unique_pointer(my_unique_pointer<T>&&p)
	{
		cout << "Move Constructor runs\n";
		this->_ptr = p._ptr;
		this->_size = p._size;
		p._ptr = nullptr;
		p._size = 0;
	}
	my_unique_pointer& operator=(my_unique_pointer<T>&& p)
	{
		cout << "Operator Move Constructor runs\n";
		this->_ptr = p._ptr;
		this->_size = p._size;
		p._ptr = nullptr;
		p._size = 0;
		return *this;
	}
	T* operator->()
	{
		return this->_ptr;
	}
	T& operator*()
	{
		return *this->_ptr;
	}
	T& operator[](int index)
	{
		return *(this->_ptr+index);
	}
	void assign(T value)
	{
		
		this->reset();
		cout << "Value assigned to My_unique_pointer\n";
		this->_ptr = new T(value);
		this->_size = 1;
		
	}
	void reset()
	{
		cout << "My_unique_pointer reseted\n";
		delete []this->_ptr;
		this->_ptr = nullptr;
		this->_size = 0;
	}
	~my_unique_pointer()
	{
		cout << "My_unique_pointer destructor destroyed\n";
		delete[]this->_ptr;
		this->_ptr = nullptr;
		this->_size = 0;
	}
};

#pragma once
#include<vector>
#include <algorithm>
#include<string>

template<class T>
class my_shared_pointer;

template<class T>
class my_weak_pointer;

template<class T>
class my_memory
{
private:
	vector<my_shared_pointer<T>*> shared_memory;
	vector<my_weak_pointer<T>*> weak_memory;
	void free()
	{
		cout << "All weak memory reseted\n";
		int size = weak_memory.size();
		for (int i=0;i<size;i++)
		{
			weak_memory[0]->reset();
		}
		delete this;
	}
public:
	my_memory()
	{
		cout << "Memory Constructor runs\n";
	}
	void assign( my_shared_pointer<T>& p)
	{
		cout << "Assigning shared ptr to memory\n";
		this->shared_memory.push_back(&p);
	}
	void free(my_shared_pointer<T>& p)
	{
		cout << "Freeing shared ptr from memory\n";
		shared_memory.erase(remove(shared_memory.begin(), shared_memory.end(), &p), shared_memory.end());
		if (this->shared_memory.size()==0)
		{
			p.delete_refered_object();	
			this->free();
		}
	}

	void assign(my_weak_pointer<T>& p)
	{
		cout << "Assigning weak ptr to memory\n";
		weak_memory.push_back(&p);
	}
	void free(my_weak_pointer<T>& p)
	{
		cout << "Freeing weak ptr from memory\n";
		weak_memory.erase(remove(weak_memory.begin(), weak_memory.end(), &p),weak_memory.end());
	}

	
	
	int count()
	{
		return shared_memory.size();
	}
};

template<class T>
class my_weak_pointer {
private:
	T* _ptr{};
	int _size{};
	my_memory<T>* _block;
public:
	my_weak_pointer()
	{
		cout << "My_weak_pointer Constructor runs\n";
	}
	my_weak_pointer(const my_weak_pointer<T>& p)
	{
		cout << "My_weak_pointer Copy Constructor runs\n";
		this->_ptr = p._ptr;
		this->_size = p._size;
		this->_block = p._block;
		this->_block->assign(*this);
	}
	my_weak_pointer& operator=(const my_weak_pointer<T>& p)
	{
		if (this->_ptr == p._ptr)
			return *this;
		cout << "My_weak_pointer Operator Copy Constructor runs\n";
		this->reset();

		this->_ptr = p._ptr;
		this->_size = p._size;
		this->_block = p._block;
		this->_block->assign(*this);
		return *this;
	}
	void assign_shared_pointer(const my_shared_pointer<T>& p)
	{
		cout << "My_weak_pointer is assigned shared_pointer\n";

		this->reset();

		this->_ptr = p._ptr;
		this->_size = p._size;
		this->_block = p._block;
		this->_block->assign(*this);
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
		return *(this->_ptr + index);
	}
	void reset()
	{
		if(this->_block)
			this->_block->free(*this);
		this->_block = nullptr;
		this->_ptr = nullptr;
		this->_size = 0;
		cout << "My_weak_pointer reseted\n";
	}
	~my_weak_pointer()
	{
		
		if (this->_block)
			this->_block->free(*this);
		cout << "My_weak_pointer deleted\n";
	}
};


template<class T>
class my_shared_pointer {
	friend my_weak_pointer<T>;
private:
	T* _ptr{};
	int _size{};
	my_memory<T>* _block;
public:
	my_shared_pointer()
	{
		cout << "My_shared_pointer Constructor runs\n";
	}
	my_shared_pointer(int size)
	{
		cout << "My_shared_pointer Constructor runs for array\n";
		this->_ptr = new T[size];
		this->_block = new my_memory<T>;
		this->_block->assign(*this);
		this->_size = size;
	}
	my_shared_pointer(const my_shared_pointer<T>& p)
	{
		cout << "My_shared_pointer Copy Constructor runs\n";

		this->_ptr = p._ptr;
		this->_size = p._size;
		this->_block = p._block;
		this->_block->assign(*this);
	}
	my_shared_pointer& operator=(const my_shared_pointer<T>& p)
	{
		if (this->_ptr == p._ptr)
			return *this;
		
		cout << "My_shared_pointer Operator Copy Constructor runs\n";
		this->reset();

		this->_ptr = p._ptr;
		this->_size = p._size;
		this->_block = p._block;
		this->_block->assign(*this);

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
		return *(this->_ptr + index);
	}
	void assign(T value)
	{
		this->reset();
		this->_block = new my_memory<T>;
		this->_block->assign(*this);
		this->_ptr = new T(value);
		this->_size = 1;
		cout << "Value assigned to My_shared_pointer\n";
	}
	void reset()
	{
		if (this->_block)
			this->_block->free(*this);
		this->_block = nullptr;
		this->_ptr = nullptr;
		this->_size = 0;
		cout << "My_shared_pointer reseted\n";
	}
	void delete_refered_object()
	{
		cout << "Deleting referenced objects\n";
		delete[]this->_ptr;
		this->_ptr = nullptr;
	}
	~my_shared_pointer()
	{
		if(this->_block)
			this->_block->free(*this);
		cout << "My_shared_pointer deleted\n";
	}

};

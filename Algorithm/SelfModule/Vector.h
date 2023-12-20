#pragma once

template <typename T>
class Vector {
public:
	Vector()
	{

	}

	~Vector()
	{
		if (_data) delete[] _data;
	}
	void push_back(const T& data)
	{
		if (_capacity == _size) {
			int newCapacity = _capacity * 1.5;
			if (newCapacity == _capacity) newCapacity++;
			reserve(newCapacity);
		}
		_data[_size] = data;
		_size++;
	}

	void reserve(int capacity)
	{
		if (_capacity > capacity) return;
		_capacity = capacity;
		T* newData = new T[capacity];
		// 데이터 이주작업
		for (int i = 0; i < _size; i++) newData[i] = _data[i];

		if (_data) delete[] _data;

		_data = newData;
	}

	void clear()
	{
		if (_data)
		{
			delete[] _data;
			_data = new T[_capacity];
			//현재는 간단하게 구현하기 위해서 delete로 지우지만 소멸자 호출등 고려할 부분들이 있따.


		}
		_size = 0;
	}

	int size() { return _size; }
	int capacity() { return _capacity; }
	T& operator[](int pos) { return _data[pos]; }

private:
	T* _data = nullptr;
	int _size = 0;
	int _capacity = 0;

};
#pragma once
#include <vector>

template <typename T>
class Queue{
public:
	Queue() {
		_container.resize(100);
	}
	//1. [-][-][front][1][2][3][4][5][6][back]
	//2/ [3][back][-][-][-][front][1][2]
	void push(const T& value)
	{
		if (_size == _container.size())
		{
			int newSize = std::max(1,_size * 2);
			std::vector<T> newData;
			newData.resize(newSize);

			for (int i = 0; i < _size; i++)
			{
				int index = (_front + i) % _container.size();
				newData[i] = _container[index];
			}
			_container.swap(newData);
			_front = 0;
			_back = _size;
		}
		_container[_back] = value;
		_back = (_back + 1) % _container.size(); // 2�� ���� ���� back�� �ѹ��� ����� ����ؼ� % ����
		_size++;
	}
	void pop()
	{
		_front = (_front + 1) % _container.size(); // �ܼ��� front�� ������Ű�� ��
		_size--;
	}
	T& front() 
	{
		return _container[_front];
	}
	bool empty()
	{
		return size == 0;
	}
	int size()
	{
		return _size;
	}
private:
	std::vector<T> _container;
	int _back = 0;
	int _front = 0;
	int _size = 0;

};
#pragma once
template <typename T>
struct StackNode {
	T _data;
	StackNode* _next;
};

template <typename T>
class Stack {
public:
	// head <= tail
	// head <= Node <= tail
	// head <= Node <= newNode <= tail
	// head <= Node <= newNode <= newNode2 <=tail
	Stack()
	{
		head = new StackNode<T>;
		tail = new StackNode<T>;
		tail->_next = head;
	}
	~Stack()
	{
		delete head;
		delete tail;
	}
	void push(const T& value)
	{
		StackNode<T>* newNode = new StackNode<T>;
		newNode->_next = tail->_next;
		newNode->_data = value;
		tail->_next = newNode;
		_size++;
	}
	void pop()
	{
		StackNode<T>* tmpNode = tail->_next;
		tail->_next = tmpNode->_next;
		delete tmpNode;
		_size--;
	}
	
	T& top()
	{
		return (tail->_next)->_data;
	}
	int size() { return _size; }
	bool empty() { return _size == 0; }


private:
	StackNode<T>* head;
	StackNode<T>* tail;
	int _size = 0;
};
#pragma once

template <typename T>
struct Node {
public:
	Node() : _prev(nullptr), _next(nullptr), _data(int())
	{

	}
	Node(const T& value) : _prev(nullptr), _next(nullptr), _data(value)
	{

	}

	Node* _prev;
	Node* _next;
	T		_data;
};	// 이건 지들끼리 연결할꺼고

template <typename T>
class Iterator {
public:
	Node<T>* _node;
	Iterator() : _node(nullptr) {

	}
	Iterator(Node<T>* node) : _node(node)
	{

	}
	// ++ it
	Iterator& operator++()
	{
		_node = _node->_next;
		return *this;
	}
	// it ++
	Iterator& operator++(int)
	{
		_node = _node->_next;
		return *this;
	}
	// -- it
	Iterator& operator--()
	{
		_node = _node->_prev;
		return *this;
	}
	// it ++
	Iterator& operator--(int)
	{
		_node = _node->_prev;
		return *this;
	}

	T& operator*()
	{
		return _node->_data;
	}
	bool operator==(const Iterator& other)
	{
		return _node == other._node;
	}

	bool operator!=(const Iterator& other)
	{
		return _node != other._node;
	}


};

template <typename T>
class List {
public:
	List() : _size(0)
	{	// [head] <-> ... <-> [tail]
		_head = new Node<T>();
		_tail = new Node<T>();	// 처음 list생성할때 가리키도록 더미노드 생성
		_head->_next = _tail;
		_tail->_prev = _head;
	}
	~List()
	{	
		while (_size > 0)
		{
			pop_back();
		}
		delete _head;
		delete _tail;
	}

	int size() { return _size; }
	void push_back(const T& value)
	{
		AddNode(_tail, value);
	}

	void pop_back()
	{
		RemoveNode(_tail->_prev);
	}
private:
	// [head] <=> [1] <=> ... <=> prevNode <=> newNode <=> before <=> ... <=> [tail]
	Node<T>* AddNode(Node<T>* before, const T& value)
	{
		Node<T>* newNode = new Node<T>(value);
		Node<T>* prevNode = before->_prev;

		prevNode->_next = newNode;
		newNode->_prev = prevNode;
		newNode->_next = before;
		before->_prev = newNode;
		
		_size++;

		return newNode;
	}

	Node<T>* RemoveNode(Node<T>* node)
	{
		Node<T>* prevNode = node->_prev;
		Node<T>* nextNode = node->_next;

		prevNode->_next = nextNode;
		nextNode->_prev = prevNode;

		delete node;

		_size--;

		return nextNode;
	}
public:
	using iterator = Iterator<T>;
	iterator begin() { return iterator(_head->_next); }
	iterator end() { return iterator(_tail); }
	iterator insert(iterator it, const T& value)
	{	// it 앞에 넣어줄것.
		Node<T>* node = AddNode(it._node, value);
		return iterator(node);
	}
	iterator erase(iterator it)
	{
		Node<T>* node = RemoveNode(it._node);
		return iterator(node);
	}
private:
	Node<T>* _head;
	Node<T>* _tail;
	int		 _size;
};	// 이건 전체적으로 봤을떄 맨 앞 과 끝
#include <iostream>
#include <windows.h>
#include "BinarySearchTree.h"

void SetCursorPosition(int x, int y)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(output, pos);
}

void BinarySearchTree::insert(int key)
{
	Node* newNode = new Node();
	newNode->key = key;
	if (_root == nullptr)
	{
		_root = newNode;
		return;
	}

	Node* node = _root;
	Node* parent = nullptr;
	while (node)
	{
		parent = node;
		if (key < node->key) node = node->left;
		else node = node->right;
	}
	newNode->parent = parent;
	if (key < parent->key) parent->left = newNode;
	else parent->right = newNode;
}

Node* BinarySearchTree::Search(Node* node, int key)
{
	if (node == nullptr || key == node->key) return node;
	if (node->key < key) Search(node->right, key);
	else if (node->key > key) Search(node->left,key);

}

Node* BinarySearchTree::Search2(Node* node, int key)
{
	while (node->key != key && node)
	{
		if (key < node->key) node = node->left;
		else node = node->right;
	}
	return node;

}

Node* BinarySearchTree::Min(Node* node)
{
	while (node->left != nullptr)
	{
		node = node->left;
	}
	return node;
}

Node* BinarySearchTree::Max(Node* node)
{
	
	while (node->right != nullptr)
	{
		node = node->right;
	}
	return node;
}

Node* BinarySearchTree::Next(Node* node)
{
	//���� ������ ��尡 �ִٸ� �� ��忡�� ���� ���ʿ��ִ°� �� ������.(Ȥ�� �����̰ų�)
	if (node->right) return Min(node->right); 
	Node* parent = node->parent;
	while (parent && node == parent->right)
	// �� ���ǿ� ���������� parent�� ������, ���� �� ���ʿ� ����������.
	{
		node = parent;
		parent = parent->parent;
	}
	return parent;
}

void BinarySearchTree::Delete(int key)
{
	// 1. child�� �ϳ��� ���°�� -> �����ְ� ��
	// 2. �ڽ��� �� �ϳ��� �ִ°�� -> �ڽ��� ���� �ø��� �ڽ��� ����.
	// 3. �ڽ��� �θ��ΰ�� -> �ڱ⺸�� �������� ū ���� ã�Ƽ� �־��ش���, 
	// �ߺ��� ���� ����.
}

void BinarySearchTree::Print(Node* node, int x, int y)
{
	if (node == nullptr) return;
	SetCursorPosition(x, y);
	std::cout << node->key;
	Print(node->left, x - (10 / (y + 1)), y + 1);
	Print(node->right, x + (10 / (y + 1)), y + 1);
}

void BinarySearchTree::Print_Inorder(Node* node)
{
	if (node == nullptr) return;

	std::cout << node->key << std::endl;
	Print_Inorder(node->left);
	Print_Inorder(node->right);
}

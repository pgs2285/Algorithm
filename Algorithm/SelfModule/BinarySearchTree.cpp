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
	//만약 오른쪽 노드가 있다면 그 노드에서 가장 왼쪽에있는게 그 다음값.(혹은 본인이거나)
	if (node->right) return Min(node->right); 
	Node* parent = node->parent;
	while (parent && node == parent->right)
	// 위 조건에 맞지않으면 parent가 있으며, 내가 그 왼쪽에 있을때까지.
	{
		node = parent;
		parent = parent->parent;
	}
	return parent;
}

void BinarySearchTree::Delete(int key)
{
	// 1. child가 하나도 없는경우 -> 날려주고 끝
	// 2. 자식이 딱 하나만 있는경우 -> 자식을 위로 올리고 자신은 삭제.
	// 3. 자식이 두명인경우 -> 자기보다 다음으로 큰 수를 찾아서 넣어준다음, 
	// 중복된 수는 삭제.
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

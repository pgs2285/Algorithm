#include <windows.h>
#include <iostream>
#include "RedBlackTree.h"

enum class ConsoleColor
{
	BLACK = 0,
	RED = FOREGROUND_RED,
	GREEN = FOREGROUND_GREEN,
	BLUE = FOREGROUND_BLUE,
	YELLOW = RED | GREEN,
	WHITE = RED | GREEN | BLUE,
};
void SetCursorPosition(int x, int y)
{	// Ŀ����ġ ����
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(output, pos);
}

void SetCursorColor(ConsoleColor color)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::SetConsoleTextAttribute(output, static_cast<SHORT>(color));
}


void RedBlackTree::Print(Node* node, int x, int y)
{
	if (node == nullptr) 
		return;
	SetCursorPosition(x, y);

	if (node->color == Color::Black)
		SetCursorColor(ConsoleColor::BLACK);
	else
		SetCursorColor(ConsoleColor::RED);
	std::cout << node->key;
	Print(node->left, x - (5 / (y + 1)), y + 1);
	Print(node->right, x + (5 / (y + 1)), y + 1);

	SetCursorColor(ConsoleColor::WHITE);
}

void RedBlackTree::Insert(int key)
{
	Node* newNode = new Node();
	newNode->key = key;

	Node* node = _root;
	Node* parent = _nil;

	while (node != _nil)
	{
		parent = node;
		if (node->key > key)
			node = node->left;
		else
			node = node->right;
	}

	newNode->parent = parent;

	if (parent == _nil)
		_root = newNode;
	else if (key < parent->key)
		parent->left = newNode;
	else
		parent->right = newNode;
	
	// Red Black �˻�
	newNode->left = _nil;
	newNode->right = _nil;
	newNode->color = Color::Red; // ���ο� ���� �׻� ������

	InsertFixup(newNode);
}

void RedBlackTree::InsertFixup(Node* node)
{
	// 1) parent = red && uncle = red
	// 2) parent = red && uncle = black(triangle) (root-left-right �����ΰ��(right->left�� ����))
	// 3) parent = red && uncle = black(list) (root-left-left �����ΰ��(right-right������))
	// ���⼭ uncle�� �θ���� �������


	while (node->parent->color == Color::Red) // red-red�� �ȵǴϱ� (�����尡 ������������)
	{
	

	
		if (node->parent == node->parent->parent->left) // �θ��尡 �� �θ��� ���ʿ� �ִ°�?
		{// nil��� ���� null check�� �����ʾƵ� �ȴ�.(�ҳ��� �����)
			Node* uncle = node->parent->parent->right; // �� ��쿡�� �Ҿƹ����� �������� uncle
#pragma region ����(Recoloring)
//			[ppp]
//		[pp[black]]
//	[p[red]]	[uncle(red)]
//		[n[red]]
//�� case
#pragma endregion
			if (uncle->color == Color::Red) 
			{// �̰��� parent�� ��, uncle�� ��, pp�� red�� �ٲپ��ֱ�. (Recoloring)
				node->parent->parent->color = Color::Red;
				node->parent->color = Color::Black;
				uncle->color = Color::Black;

				node = node->parent->parent; // ppp�� Red�� ����Ǵ� while���� ���� �����͵鵵 ����.
			}
#pragma region ����(Restructing)
//			[ppp]
//		[pp[black]]
//	[p[red]]	[uncle(black)]
//		[n[red]]
//�� case
#pragma endregion
			else
			{ 
				if (node == node->parent->right) // triangle type(���� if������ �θ� �������� �����̶��� üũ������)
				{
					// ���ش�
				}
			}

		}
		else
		{

		}
	}
}

#pragma region ����(LeftRotate)
/*
*			before
*	       [y]
*	 [x]		[3]
*[1]     [2]
* 
*			after
* 
*		   [x]
*	 [1]		[y]
*			[2]		[3]
*/
#pragma endregion
void RedBlackTree::LeftRotate(Node* node)
{
}

void RedBlackTree::RightRotate(Node* node)
{
}

Node* RedBlackTree::Search(Node* node, int key)
{
	if (node == _nil || key == node->key)
		return node;
	if (key > node->key) 
		return Search(node->right, key);
	else 
		return Search(node->left, key);
	return nullptr;
}

Node* RedBlackTree::Max(Node* node)
{
	while (node->right != _nil) 
		node = node->right;
	return node;
}

Node* RedBlackTree::Min(Node* node)
{
	while (node->left != _nil) 
		node = node->left;
	return node;
}

Node* RedBlackTree::Next(Node* node)
{
	if (node->right != _nil)
		return Min(node->right);

	Node* parent = node->parent;

	while (parent != _nil && node == parent->right)
	{
		node = parent;
		parent = parent->parent;
	}
	return parent;
}



RedBlackTree::RedBlackTree()
{
	_nil = new Node();
	_root = _nil; 
}

RedBlackTree::~RedBlackTree()
{
	delete _nil;
}

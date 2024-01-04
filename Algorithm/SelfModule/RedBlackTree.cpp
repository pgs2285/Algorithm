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
void SetCursorPosition2(int x, int y)
{	// 커서위치 변경
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
	if (node == _nil) 
		return;
	SetCursorPosition2(x, y);

	if (node->color == Color::Black)
		SetCursorColor(ConsoleColor::BLUE);
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
	
	// Red Black 검사
	newNode->left = _nil;
	newNode->right = _nil;
	newNode->color = Color::Red; // 새로운 노드는 항상 레드노드

	InsertFixup(newNode);
}

void RedBlackTree::InsertFixup(Node* node)
{
	// 1) parent = red && uncle = red
	// 2) parent = red && uncle = black(triangle) (root-left-right 구조인경우(right->left도 포함))
	// 3) parent = red && uncle = black(list) (root-left-left 구조인경우(right-right도포함))
	// 여기서 uncle은 부모님의 형제노드


	while (node->parent->color == Color::Red) // red-red는 안되니까 (더블레드가 없어질때까지)
	{
	

	
		if (node->parent == node->parent->parent->left) // 부모노드가 그 부모의 왼쪽에 있는가?
		{// nil노드 덕에 null check는 하지않아도 된다.(닐노드는 블랙노드)
			Node* uncle = node->parent->parent->right; // 이 경우에선 할아버지의 오른쪽이 uncle
#pragma region 설명(Recoloring)
//			[ppp]
//		[pp[black]]
//	[p[red]]	[uncle(red)]
//		[n[red]]
//인 case
#pragma endregion
			if (uncle->color == Color::Red) 
			{// 이경우는 parent는 블랙, uncle도 블랙, pp는 red로 바꾸어주기. (Recoloring)
				node->parent->parent->color = Color::Red;
				node->parent->color = Color::Black;
				uncle->color = Color::Black;

				node = node->parent->parent; // ppp가 Red면 위배되니 while문을 통해 이전것들도 수정.
			}
#pragma region 설명(Restructing)
//			[ppp]
//		[pp[black]]
//	[p[red]]	[uncle(black)]
//		[n[red]]
//인 case
#pragma endregion
			else
			{ 
				if (node == node->parent->right) // triangle type(위에 if문으로 부모가 조상노드의 왼쪽이란걸 체크햇으니)
				{
					// 펴준다
					node = node->parent;
					LeftRotate(node);
				}
				node->parent->color = Color::Black;
				node->parent->parent->color = Color::Red;
				RightRotate(node->parent->parent);
			}

		}
		else // 위 와는 반대상황
		{
			Node* uncle = node->parent->parent->left; 

			if (uncle->color == Color::Red)
			{// 이경우는 parent는 블랙, uncle도 블랙, pp는 red로 바꾸어주기. (Recoloring)
				node->parent->parent->color = Color::Red;
				node->parent->color = Color::Black;
				uncle->color = Color::Black;

				node = node->parent->parent; // ppp가 Red면 위배되니 while문을 통해 이전것들도 수정.
			}

			else
			{
				if (node == node->parent->left) // triangle type(위에 if문으로 부모가 조상노드의 왼쪽이란걸 체크햇으니)
				{
					// 펴준다
					node = node->parent;
					RightRotate(node);
				}
				node->parent->color = Color::Black;
				node->parent->parent->color = Color::Red;
				LeftRotate(node->parent->parent);
			}
		}
	}
	_root->color = Color::Black;
}
#pragma region 설명(LeftRotate)
/*
		before
*
*		   [x]
*	 [1]		[y]
*			   [2][3]
* 
*		after
* 
*			[y]
*		[x]		[3]
*	  [1][2]
*/
#pragma endregion
void RedBlackTree::LeftRotate(Node* x)
{
	Node* y = x->right;
	x->right = y->left;
	if(y->left != _nil)
		y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == _nil)
		_root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;

	y->left = x;
	x->parent = y;

}
#pragma region 설명(RightRotate)
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
void RedBlackTree::RightRotate(Node* y)
{
	Node* x = y->left;
	y->left = x->right;
	if(x->right != _nil)
		x->right->parent = y;

	x->parent = y ->parent;
	if (y->parent == _nil)
		_root = x;
	else if (y->parent->left == y)
		y->parent->left = x;
	else
		y->parent->right = x;
	y->parent = x;
	x->right = y;

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

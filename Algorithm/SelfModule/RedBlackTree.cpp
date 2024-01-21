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

void ShowConsoleCursor(bool flag)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	::GetConsoleCursorInfo(output, &cursorInfo);
	cursorInfo.bVisible = flag;
	::SetConsoleCursorInfo(output, &cursorInfo);
}

void RedBlackTree::Print()
{
	::system("cls");
	Print(_root, 10, 0);
	ShowConsoleCursor(false);
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
					node = node->parent;
					LeftRotate(node);
				}
				node->parent->color = Color::Black;
				node->parent->parent->color = Color::Red;
				RightRotate(node->parent->parent);
			}

		}
		else // �� �ʹ� �ݴ��Ȳ
		{
			Node* uncle = node->parent->parent->left; 

			if (uncle->color == Color::Red)
			{// �̰��� parent�� ��, uncle�� ��, pp�� red�� �ٲپ��ֱ�. (Recoloring)
				node->parent->parent->color = Color::Red;
				node->parent->color = Color::Black;
				uncle->color = Color::Black;

				node = node->parent->parent; // ppp�� Red�� ����Ǵ� while���� ���� �����͵鵵 ����.
			}

			else
			{
				if (node == node->parent->left) // triangle type(���� if������ �θ� �������� �����̶��� üũ������)
				{
					// ���ش�
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
#pragma region ����(LeftRotate)
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
#pragma region ����(RightRotate)
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

void RedBlackTree::Replace(Node* u, Node* v)
{
	if (u->parent == _nil)
		_root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent -> right = v;

	if (v)
		v->parent = u->parent;

	delete u;
}

void RedBlackTree::Delete(int key)
{
	Node* deleteNode = Search(_root, key);
	Delete(deleteNode);
}

void RedBlackTree::Delete(Node* node)
{
	if (node == _nil)
		return;

	if (node->left == _nil)
	{
		Color color = node->color; // ������ ����� ����м�
		Node* right = node->right;
		Replace(node, node->right);

		if (color == Color::Black)
			DeleteFixup(right);
	}
	else if (node->right == _nil)
	{
		Color color = node->color;
		Node* left = node->left;
		Replace(node, node->left);

		if (color == Color::Black)
			DeleteFixup(left);
	}
	else
	{
		Node* next = Next(node);
		node->key = next->key;
		Delete(next);
	}
}

void RedBlackTree::DeleteFixup(Node* node)
{
	Node* x = node;
	while (x != _root && x->color == Color::Black)
	{ // case 1, 2 
		if (x == x->parent->left)
		{
			Node* s = x->parent->right; // �������
			if (s->color == Color::Red)
			{
				// case 2-1�� �ǰ���(Readme ����) ������带 Black, �θ��带 Red�� �ٲپ��ش�.
				s->color = Color::Black;
				x->parent->color = Color::Red;
				// �� ��쿡�� ������ double black�� ��Ȳ�̴� left rotation
				LeftRotate(x->parent);
				s = x->parent->right;
			}
			if (s->left->color == Color::Black && s->right->color == Color::Black)
			{	// case 2-2 : �߰� BLACK�� �θ𿡰� �������ش�. -> �θ� RED�̸� BLACK�� �ȴ�. �θ� BLACK�̶�� DB���°� �ȴ�. ������ RED.
				s->color = Color::Red;
				x = x->parent; // ���������� �ָ� parent�θ� �ٲ��൵ �ڵ����� ����ɰ�.
			}
			else // ���� ���� �������� ������ �ڽ��� �ϳ��� red
			{	// case 2-3 (DB�� ������ BLACK�̰�, ������ near �ڽ��� RED, ������ far �ڽ��� BLACK�� ���)
				if (s->right->color == Color::Black)
				{// near=BLACK, ������� = RED(s�� near ����ȯ) far�������� Rotate���ش�.
					s->left->color = Color::Black;
					s->color = Color::Red;
					RightRotate(s);
					s = x->parent->right;
				}

				// case 2-4(������ far�ڽ��� RED �ΰ��) : p�� s������ ��ȯ�ϰ� far = BLACK���� �ٲپ��ְ�, DB�������� Rotate,
				s->color = x->parent->color;
				x->parent->color = Color::Black;
				s->right->color = Color::Black;
				LeftRotate(x->parent);
				x = _root;
			}
		}
		else
		{
			Node* s = x->parent->left; // �������
			if (s->color == Color::Red)
			{
				s->color = Color::Black;
				x->parent->color = Color::Red;
				RightRotate(x->parent);
				s = x->parent->left;
			}
			if (s->right->color == Color::Black && s->left->color == Color::Black)
			{	// case 2-2 : �߰� BLACK�� �θ𿡰� �������ش�. -> �θ� RED�̸� BLACK�� �ȴ�. �θ� BLACK�̶�� DB���°� �ȴ�. ������ RED.
				s->color = Color::Red;
				x = x->parent;
			}
			else // ���� ���� �������� ������ �ڽ��� �ϳ��� red
			{	// case 2-3 (DB�� ������ BLACK�̰�, ������ near �ڽ��� RED, ������ far �ڽ��� BLACK�� ���)
				if (s->left->color == Color::Black)
				{// near=BLACK, ������� = RED(s�� near ����ȯ) far�������� Rotate���ش�.
					s->right->color = Color::Black;
					s->color = Color::Red;
					LeftRotate(s);
					s = x->parent->left;
				}

				// case 2-4(������ far�ڽ��� RED �ΰ��) : p�� s������ ��ȯ�ϰ� far = BLACK���� �ٲپ��ְ�, DB�������� Rotate,
				s->color = x->parent->color;
				x->parent->color = Color::Black;
				s->left->color = Color::Black;
				RightRotate(x->parent);
				x = _root;
			}

		}
		x->color = Color::Black;
	}
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

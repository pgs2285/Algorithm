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
		Color color = node->color; // 삭제할 노드의 색상분석
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
			Node* s = x->parent->right; // 형제노드
			if (s->color == Color::Red)
			{
				// case 2-1에 의거해(Readme 참조) 형제노드를 Black, 부모노드를 Red로 바꾸어준다.
				s->color = Color::Black;
				x->parent->color = Color::Red;
				// 이 경우에는 왼쪽이 double black인 상황이니 left rotation
				LeftRotate(x->parent);
				s = x->parent->right;
			}
			if (s->left->color == Color::Black && s->right->color == Color::Black)
			{	// case 2-2 : 추가 BLACK을 부모에게 이전해준다. -> 부모가 RED이면 BLACK이 된다. 부모가 BLACK이라면 DB상태가 된다. 형제는 RED.
				s->color = Color::Red;
				x = x->parent; // 다음실행할 애를 parent로만 바꿔줘도 자동으로 실행될것.
			}
			else // 여기 들어온 순간부터 형제의 자식중 하나는 red
			{	// case 2-3 (DB의 형제가 BLACK이고, 형제의 near 자식이 RED, 형제의 far 자식이 BLACK인 경우)
				if (s->right->color == Color::Black)
				{// near=BLACK, 형제노드 = RED(s와 near 색상교환) far방향으로 Rotate해준다.
					s->left->color = Color::Black;
					s->color = Color::Red;
					RightRotate(s);
					s = x->parent->right;
				}

				// case 2-4(형제의 far자식이 RED 인경우) : p와 s색상을 교환하고 far = BLACK으로 바꾸어주고, DB방향으로 Rotate,
				s->color = x->parent->color;
				x->parent->color = Color::Black;
				s->right->color = Color::Black;
				LeftRotate(x->parent);
				x = _root;
			}
		}
		else
		{
			Node* s = x->parent->left; // 형제노드
			if (s->color == Color::Red)
			{
				s->color = Color::Black;
				x->parent->color = Color::Red;
				RightRotate(x->parent);
				s = x->parent->left;
			}
			if (s->right->color == Color::Black && s->left->color == Color::Black)
			{	// case 2-2 : 추가 BLACK을 부모에게 이전해준다. -> 부모가 RED이면 BLACK이 된다. 부모가 BLACK이라면 DB상태가 된다. 형제는 RED.
				s->color = Color::Red;
				x = x->parent;
			}
			else // 여기 들어온 순간부터 형제의 자식중 하나는 red
			{	// case 2-3 (DB의 형제가 BLACK이고, 형제의 near 자식이 RED, 형제의 far 자식이 BLACK인 경우)
				if (s->left->color == Color::Black)
				{// near=BLACK, 형제노드 = RED(s와 near 색상교환) far방향으로 Rotate해준다.
					s->right->color = Color::Black;
					s->color = Color::Red;
					LeftRotate(s);
					s = x->parent->left;
				}

				// case 2-4(형제의 far자식이 RED 인경우) : p와 s색상을 교환하고 far = BLACK으로 바꾸어주고, DB방향으로 Rotate,
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

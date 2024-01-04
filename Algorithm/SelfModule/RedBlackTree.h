#pragma once
enum class Color
{
	Red = 0,
	Black = 1,
};

struct Node
{
	Node* parent = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;

	int key = {};
	Color color = Color::Black;
};
//Red-Black Tree
//1) 모든 노드는 Red or Black이다
//2) Root는 Black
//3) Leaf(NIL)은 Black
//4) Red노드의 자식은 Black(연속해서 Red-Red X)
//5) 각 노드로부터 - 리프까지 가는 경로들은 모두 같은 수의 black노드를 만난다.
class RedBlackTree
{
public:
	RedBlackTree();
	~RedBlackTree();

	void Print(Node* node, int x, int y);
	void Insert(int key);
	//노드가 규칙을 잘 지키는가
	void InsertFixup(Node* node);
	void LeftRotate(Node* node);
	void RightRotate(Node* node);

	Node* Search(Node* node, int key);
	Node* Max(Node* node);
	Node* Min(Node* node);
	Node* Next(Node* node);
	

private:
	Node* _root = nullptr;
	Node* _nil = nullptr; // 이제는 nullptr을 사용하지 않고 nil 노드를 통해 단말노드인지 확인.
	// 굳이 _nil을 여러개 만들지 않아도 공용으로 사용하면 된다.
};


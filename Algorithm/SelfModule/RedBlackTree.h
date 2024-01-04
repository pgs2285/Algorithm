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
//1) ��� ���� Red or Black�̴�
//2) Root�� Black
//3) Leaf(NIL)�� Black
//4) Red����� �ڽ��� Black(�����ؼ� Red-Red X)
//5) �� ���κ��� - �������� ���� ��ε��� ��� ���� ���� black��带 ������.
class RedBlackTree
{
public:
	RedBlackTree();
	~RedBlackTree();

	void Print(Node* node, int x, int y);
	void Insert(int key);
	//��尡 ��Ģ�� �� ��Ű�°�
	void InsertFixup(Node* node);
	void LeftRotate(Node* node);
	void RightRotate(Node* node);

	Node* Search(Node* node, int key);
	Node* Max(Node* node);
	Node* Min(Node* node);
	Node* Next(Node* node);
	

private:
	Node* _root = nullptr;
	Node* _nil = nullptr; // ������ nullptr�� ������� �ʰ� nil ��带 ���� �ܸ�������� Ȯ��.
	// ���� _nil�� ������ ������ �ʾƵ� �������� ����ϸ� �ȴ�.
};


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

private:
	Node* _root = nullptr;
	Node* _nil = nullptr; // ������ nullptr�� ������� �ʰ� nil ��带 ���� �ܸ�������� Ȯ��.
	// ���� _nil�� ������ ������ �ʾƵ� �������� ����ϸ� �ȴ�.
};


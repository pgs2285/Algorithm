#pragma once
struct Node
{
	Node* parent = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;
	int key = {};
};
class BinarySearchTree
{
public:
	void insert(int key);
	//Search�� ����Լ� ����
	Node* Search(Node* node, int key);
	Node* Search(int key) { return Search(_root, key); }
	//Search2 �� �ݺ��� Ž������
	Node* Search2(Node* node, int key);
	Node* Search2(int key) { return Search2(_root, key); }

	Node* Min(Node* node);
	Node* Min() { return Min(_root); }
	Node* Max(Node* node);
	Node* Max() { return Max(_root); }
	Node* Next(Node* node);
	Node* Next(int key) { return Next(Search(key)); }

	void Delete(int key);
	void Delete(Node* node);

	void Replace(Node* u, Node* v);

	void Print() { Print(_root, 10, 0); }
	void Print(Node* node, int x, int y);
	// ������ȸ preorder 
	// ������ȸ inorder
	// ������ȸ postorder
	void Print_Inorder() { Print_Inorder(_root); }
	void Print_Inorder(Node* node);
private:
	Node* _root = nullptr;
};


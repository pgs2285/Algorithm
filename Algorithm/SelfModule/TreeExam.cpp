#include <iostream>
#include <vector>
using namespace std;
using NodeRef = std::shared_ptr<struct Node>;
struct Node
{
	Node(const string& data) : data(data) {}

	string data;
	vector<NodeRef> children;
};

NodeRef CreateTree()
{
	NodeRef root = make_shared<Node>("��Ʈ");
	{
		NodeRef node = make_shared<Node>("��� 1");
		root->children.push_back(node);
		{
			NodeRef leaf = make_shared<Node>("����1");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("����2");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("����3");
			node->children.push_back(leaf);
		}
		NodeRef node2 = make_shared<Node>("��� 2");
		root->children.push_back(node2);
		{
			NodeRef leaf = make_shared<Node>("����4");
			node2->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("����5");
			node2->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("����6");
			node2->children.push_back(leaf);
		}
	}
	return root;
}

void PrintTree(NodeRef root, int depth)
{
	for (int i = 0; i < depth; i++) cout << "-";
	cout << root->data << endl;
	for (NodeRef& child : root->children)
		PrintTree(child, depth + 1);
}

int GetHeight(NodeRef root)
{
	int height = 1;
	for (NodeRef& child : root->children)
	{
		height = max(height, GetHeight(child) + 1);
	}
	return height;
}
/*
int main()
{
	NodeRef root = CreateTree();
	PrintTree(root, 0);
	cout << "Ʈ���� ���� : " << GetHeight(root);

}*/
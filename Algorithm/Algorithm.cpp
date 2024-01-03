#include <iostream>
#include <vector>
#include "SelfModule/BinarySearchTree.h"
using namespace std;

int main()
{
	BinarySearchTree bst;
	bst.insert(10);
	bst.insert(30);
	bst.insert(19);
	bst.insert(20);
	bst.insert(44);
	bst.insert(11);
	bst.insert(22);
	bst.insert(9);
	bst.Print();
	for (int i = 0; i < 5; i++) cout << endl; // 글자 초기화
	cout << "22의 부모노드는 " << bst.Search(22)->parent->key << endl; //
	cout << "22의 다음 값은(크기기준)" << bst.Next(22)->key << endl;
	cout << "현재 이진 트리의 최대값은 " << bst.Max()->key << endl;
	cout << "현재 이진 트리의 최소값은 " << bst.Min()->key << endl;
	
	//bst.Print_Inorder();
	//bst.Print();
	for (int i = 0; i < 10; i++) cout << endl; // 글자 초기화
}
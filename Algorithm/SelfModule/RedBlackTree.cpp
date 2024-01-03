#include "RedBlackTree.h"

RedBlackTree::RedBlackTree()
{
	_nil = new Node();
	_root = _nil; 
}

RedBlackTree::~RedBlackTree()
{
	delete _nil;
}

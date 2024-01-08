#include <iostream>
#include <vector>
#include <thread>
#include "SelfModule/RedBlackTree.h"

using namespace std;

int main()
{
	RedBlackTree rbt;
	rbt.Insert(30);
	rbt.Print();
	this_thread::sleep_for(1s);
	rbt.Insert(10);
	rbt.Print();
	this_thread::sleep_for(1s);
	rbt.Insert(20);
	rbt.Print();
	this_thread::sleep_for(1s);
	rbt.Insert(25);
	rbt.Print();
	this_thread::sleep_for(1s);
	rbt.Insert(40);
	rbt.Print();
	this_thread::sleep_for(1s);
	rbt.Insert(50);
	rbt.Print();
	this_thread::sleep_for(1s);
	rbt.Insert(5);
	rbt.Print();
	this_thread::sleep_for(1s);
	rbt.Insert(1);
	rbt.Print();
	this_thread::sleep_for(1s);
	rbt.Delete(20);
	rbt.Print();
	this_thread::sleep_for(1s);
	rbt.Delete(30);
	rbt.Print();
	this_thread::sleep_for(1s);
	rbt.Insert(45);
	rbt.Print();
	this_thread::sleep_for(1s);
	rbt.Delete(10);
	rbt.Print();
	this_thread::sleep_for(1s);

}
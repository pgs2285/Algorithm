#include <iostream>
#include <vector>
#include <thread>
#include "SelfModule/Sort.h"

using namespace std;

int main()
{
	vector<int> v{ 3,5,7,6,1,2,9 };
	Sort s(v);
	s.InsertSort();
	s.printV();
}
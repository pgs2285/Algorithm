#include <iostream>
#include <vector>
#include <thread>
#include "SelfModule/Sort.h"

using namespace std;

int main()
{
	vector<int> v{ 3,5,7,4,1,2,9,10 };
	Sort s(v);
	s.MergeSort(0,v.size() - 1);
	s.printV();
}
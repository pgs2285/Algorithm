#include <iostream>
#include <vector>
#include <thread>
#include "SelfModule/Sort.h"

using namespace std;

int main()
{
	vector<int> v{ 3,5,7,4,1,2,9,10,20,25,0,12,19 };
	Sort s(v);
	s.QuickSort(0,v.size() - 1);
	s.printV();
}
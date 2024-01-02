#include <iostream>
#include <vector>
#include "SelfModule/BinarySearch.h"
using namespace std;

int main()
{

	BinarySearch<int> bs;
	vector<int> vec = vector<int>{ 10,22,34,51,52,76,78,81, 88,93,99 };
	int ans = bs.binarySearch(vec, 51);
	if (ans!= -1)
	{
		cout << "위치 : " << ans << endl;
	}

}
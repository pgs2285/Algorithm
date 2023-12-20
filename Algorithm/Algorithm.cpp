// Algorithm.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include "SelfModule/Vector.h"	

using namespace std;



int main()
{
	vector<int> v;
	for (int i = 0; i < 10; ++i)
	{
		v.push_back(i);
		cout << v.size() << " " << v.capacity() << endl;
	}

	v.clear();
	cout << "클리어 후 " << endl;
	cout << v.size() << " " << v.capacity() << endl;
	v.push_back(1);
	cout << v.size() << " " << v.capacity() << endl;
	// 클리어 전 capacity 그대로 유지됨.
	
	Vector<char> V;
	
	for (int i = 0; i < 10; i++)
	{
		V.push_back('a');
		cout << V[i]  << V.size() << " " << V.capacity() << endl;
	}
	V.reserve(100); // 개수를 알면 reserve를 쓰는게 훨씬 유용하다..
}
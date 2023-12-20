// Algorithm.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <list>
#include "SelfModule/List.h"	
using namespace std;
int main()
{
	list<int> li;
	list<int>::iterator eraseIt;
	for (int i = 0; i < 10; i++)
	{
		if (i == 5) eraseIt = li.insert(li.end(), i); // 이상황에선 end앞에 넣어짐
		else li.push_back(i);
	}
	li.pop_back();
	li.erase(eraseIt);
	for (list<int>::iterator it = li.begin(); it != li.end(); it++)
	{
		cout << (*it) << endl;
	}

	List<int> li2;
	List<int>::iterator eraseIt2;
	for (int i = 0; i < 10; i++)
	{
		if (i == 5) eraseIt2 = li2.insert(li2.end(), i); // 이상황에선 end앞에 넣어짐
		else li2.push_back(i);
	}
	li2.pop_back();
	li2.erase(eraseIt2);
	for (List<int>::iterator it = li2.begin(); it != li2.end(); it++)
	{
		cout << (*it) << endl;

	}
}
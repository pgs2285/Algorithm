#include <iostream>
#include <queue>
#include "SelfModule/Queue.h"
using namespace std;
int main()
{
	queue<int> q;
	for (int i = 0; i < 10; i++) q.push(i);

	while (q.empty() == false)
	{
		int value = q.front();
		q.pop();
		cout << value << endl;
	}

	int size = q.size();
	cout << "size : " << size << endl;
	cout << "자체구현 Queue" << endl;
	queue<int> q2;
	for (int i = 0; i < 1000; i++) q2.push(i);

	while (q2.empty() == false)
	{
		int value = q2.front();
		q2.pop();
		cout << value << endl;
	}

	int size2 = q2.size();
	cout << "size : " << size2 << endl;
}
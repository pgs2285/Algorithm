#include <iostream>
#include <vector>
#include "SelfModule/Priority_queue.h"
using namespace std;

int main()
{
	Priority_queue<int> pq;
	pq.push(1);
	pq.push(2);
	pq.push(5);
	pq.push(4);
	pq.push(3);

	cout << "Predicate less<int>" << endl;
	while (pq.empty() == false)
	{
		int value = pq.top();
		pq.pop();
		cout << value << endl;
	}

	Priority_queue<int, vector<int>, greater<int>> pq2;
	pq2.push(1);
	pq2.push(2);
	pq2.push(5);
	pq2.push(4);
	pq2.push(3);

	cout << "Predicate greater<int>" << endl;
	while (pq2.empty() == false)
	{
		int value = pq2.top();
		pq2.pop();
		cout << value << endl;
	}


}
#include <iostream>
#include <stack>
#include "SelfModule/Stack.h"
using namespace std;
int main()
{
	stack<int> s;
	s.push(1);
	s.push(2);
	s.push(3);
	while (s.empty() == false)
	{
		int data = s.top();
		cout << "data : " << data << " size : " << s.size() << endl;
		s.pop(); // c#,python 등 다른언어와 다른부분은 c++ 에서는 pop한다고 맨 위 요소를 return 하지 않는다.
	}
	s.push(4);
	int data = s.top();
	cout << "data : " << data << " size : " << s.size() << endl;

	cout << "자체 구현 Stack" << endl;
	Stack<int> s2;
	s2.push(1);
	s2.push(2);
	s2.push(3);

	while (s2.empty() == false)
	{
		int data = s2.top();
		cout << "data : " << data << " size : " << s2.size() << endl;
		s2.pop(); // c#,python 등 다른언어와 다른부분은 c++ 에서는 pop한다고 맨 위 요소를 return 하지 않는다.
	}
	s2.push(4);
	int data2 = s2.top();
	cout << "data : " << data2 << " size : " << s2.size() << endl;
}
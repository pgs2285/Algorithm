#include <iostream>
#include <vector>
#include <thread>
#include "SelfModule/DisjointSet.h"

using namespace std;

int main()
{
	DisjointSet teams(1000);
	teams.Merge(10, 1); // 10번과 1번을 합쳐줌. 여기선 부모가 왼쪽에있는 10번이 된다
	int teamID = teams.Find(1);
	int teamID2 = teams.Find(10);

	teams.Merge(3, 2); // 위와 동일
	int teamID3 = teams.Find(3);
	int teamID4 = teams.Find(2);

	teams.Merge(1, 3);
	int teamID6 = teams.Find(1);
	int teamID7 = teams.Find(10);

	cout << teamID << " " << teamID2 << " " << teamID3 << " " << teamID4 << " " << teamID6 << " " << teamID7 << " ";


}
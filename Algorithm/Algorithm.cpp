#include <iostream>
#include <vector>
#include "SelfModule/BFS.h"
using namespace std;
int main()
{
	std::vector<Vertex> verteices;
	verteices.resize(6);
	std::vector<std::vector<int>> adjacent = std::vector<std::vector<int>>(6);
	adjacent[0].push_back(1);
	adjacent[0].push_back(3);
	adjacent[1].push_back(0);
	adjacent[1].push_back(2);
	adjacent[1].push_back(3);
	adjacent[3].push_back(4);
	adjacent[5].push_back(4);
	BFS bfs1(verteices,adjacent);
	bfs1.discover(0); // 간선간의 접점을 통해 탐색하는 방법
	bfs1.discoverAll();
	// 만약 혼자 끊긴 노드가 있다면 그것만 실행한다.
	for (int i = 0; i < verteices.size() - 1; i++)
	{
		cout << i << "번 노드는" << bfs1.parent[i] << "에 의해 발견되었고 시작점에서는" << bfs1.distance[i] << "만큼 떨어져 있다" << endl;
	}
	
	
}
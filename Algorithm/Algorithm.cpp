#include <iostream>
#include <vector>
#include "SelfModule/DFS.h"
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
	DFS dfs1(verteices,adjacent);
	dfs1.visit(5); // 간선간의 접점을 통해 탐색하는 방법
	dfs1.DfsEtc();
	// 만약 혼자 끊긴 노드가 있다면 그것만 실행한다.
	
	
}
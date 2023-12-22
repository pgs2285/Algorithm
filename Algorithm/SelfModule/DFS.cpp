#include <vector>
#include "DFS.h"
#include <iostream>


DFS::DFS(std::vector<Vertex> verteices, std::vector<std::vector<int>> adj)
{
	adjacent = adj;
	_verteices = verteices;
	visited = std::vector<bool>(_verteices.size(), false);
}

void DFS::visit(int here)
{

	visited[here] = true;
	std::cout << "Visited : " << here << std::endl;
	// 1. 현재 방문한 곳에 인접한 모든곳을 출력
	for (int i = 0; i < adjacent[here].size(); i++)
	{
		int there = adjacent[here][i];
		if (visited[there] == false) // 방문하지 않았다면.
		{
			visit(there);
		}
	}
}


void DFS::DfsEtc()
{
	for (int i = 0; i < _verteices.size(); i++)
	{
		
		if (visited[i] == false)
		{
			std::cout << "끊긴 노드 연결" << std::endl;
			visit(i);
		}

	}
}


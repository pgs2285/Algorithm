#include <queue>
#include <vector>
#include <iostream>
#include "BFS.h"

BFS::BFS(std::vector<Vertex> verteices, std::vector<std::vector<int>> adj)
{
	adjacent = adj;
	_vertexies = verteices;
	discovered = std::vector<bool>(_vertexies.size(), false);
	parent = std::vector<int>(6, -1);
	distance = std::vector<int>(6, -1);
}

void BFS::discover(int here)
{


	std::queue<int> q;
	q.push(here);
	discovered[here] = true;
	parent[here] = here;
	distance[here] = 0;

	while (q.empty() == false)
	{
		here = q.front();
		q.pop();

		std::cout << "Visited : " << here << std::endl;
		for (int there : adjacent[here])
		{	// 현재 연결되어 있는 목록 확인
			if (discovered[there]) continue;
			q.push(there);
			discovered[there] = true;

			parent[there] = here;
			distance[there] = distance[here] + 1;
		}
	}
}

void BFS::discoverAll()
{
	for (int i = 0; i < _vertexies.size(); i++)
	{
		if (!discovered[i]) discover(i);
	}
}

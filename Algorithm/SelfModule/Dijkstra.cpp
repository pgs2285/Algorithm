#include <vector>
#include <iostream>
#include "Dijkstra.h"

Dijkstra::Dijkstra(std::vector<Vertex> vertices, std::vector<std::vector<int>> adjacent)
{
	_vertices = vertices;
	_adjacent = adjacent;
}

void Dijkstra::findPath(int here)
{
	struct VertexCost {
		int vertex;
		int cost;
	};

	std::vector<VertexCost> discovered;
	std::vector<uint32_t> best(_vertices.size(), INT32_MAX); // 각 정점별로 지금까지 발견한 최소거리 저장. 
	std::vector<int> parent(_vertices.size(), -1);
	best[here] = 0;
	parent[here] = here;
	discovered.push_back(VertexCost{ here, 0 });

	while (discovered.empty() == false)
	{
		std::vector<VertexCost>::iterator bestIt;
		int bestCost = INT32_MAX;
		
		for (auto it = discovered.begin(); it != discovered.end(); it++)
		{
			if (it->cost < bestCost)
			{
				bestCost = it->cost;
				bestIt = it;
			}
		}

		int cost = bestIt->cost;
		here = bestIt->vertex;
		discovered.erase(bestIt);

		if (best[here] < cost) continue;

		for (int there = 0; there < _vertices.size(); there++)
		{
			if (_adjacent[here][there] == -1) continue;
			int nextCost = best[here] + _adjacent[here][there];

			if (nextCost >= best[there]) continue;
			best[there] = nextCost;

			discovered.push_back(VertexCost{ there, nextCost });
			parent[there] = here;
		}
	}
	std::cout << "각 노드별 최단 cost" << std::endl;
 	for (int i = 0; i < _vertices.size(); i++)
	{
		std::cout << i << " : " << best[i] << std::endl;
	}
	for(int i = 0 ; i < _vertices.size(); i++)
	std::cout << i <<"번 노드의 부모는 : " << parent[i] << std::endl;
}

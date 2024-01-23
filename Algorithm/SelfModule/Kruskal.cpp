#include <vector>
#include "DisjointSet.h"
#include <algorithm>
#include "Kruskal.h"

int Kruskal::costSum()
{
	int ret = 0;
	selected.clear();
	std::vector<CostEdge> edges;
	for (int u = 0; u < _adjacent.size(); u++)
	{
		for (int v = 0; v < _adjacent[u].size(); v++)
		{
			int cost = _adjacent[u][v];
			if (u > v)
				continue; // 한쪽만 추가
			if (cost == -1)
				continue;
			edges.push_back(CostEdge{cost, u, v}); // 일단 모든간선 사이 넣어주기

		}
	}
	std::sort(edges.begin(), edges.end());

	DisjointSet sets(_vertex.size());

	for (CostEdge& edge : edges)
	{
		// 같은 그룹이면 스킵
		if (sets.Find(edge.u) == sets.Find(edge.v))// 저번에 find는 최상위 부모찾게 했었음. 적용까지
			continue;
		// 두그룹 합치기
		sets.Merge(edge.u, edge.v);
		selected.push_back(edge);
		ret += edge.cost;
	}
	return ret;
}

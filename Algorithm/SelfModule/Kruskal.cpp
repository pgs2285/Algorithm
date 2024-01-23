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
				continue; // ���ʸ� �߰�
			if (cost == -1)
				continue;
			edges.push_back(CostEdge{cost, u, v}); // �ϴ� ��簣�� ���� �־��ֱ�

		}
	}
	std::sort(edges.begin(), edges.end());

	DisjointSet sets(_vertex.size());

	for (CostEdge& edge : edges)
	{
		// ���� �׷��̸� ��ŵ
		if (sets.Find(edge.u) == sets.Find(edge.v))// ������ find�� �ֻ��� �θ�ã�� �߾���. �������
			continue;
		// �α׷� ��ġ��
		sets.Merge(edge.u, edge.v);
		selected.push_back(edge);
		ret += edge.cost;
	}
	return ret;
}

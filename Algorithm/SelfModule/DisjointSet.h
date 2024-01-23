#pragma once
#include <vector>
class DisjointSet
{
public:
	DisjointSet(int n) : _parent(n), _rank(n, 1)
	{
		for (int i = 0; i < n; i++)
		{
			_parent[i] = i;
		}
	}
	// ������ ã��
	int Find(int u)
	{
		if (u == _parent[u])
		{
			return u;
		}
		return _parent[u] = Find(_parent[u]); // �ֻ��� �θ������ �ڽ��� �޾���
	}

	void Merge(int u, int v)
	{
		u = Find(u);
		v = Find(v);

		if (u == v)
			return; // �ֻ��� �θ� ������ �׳� return
		
		if (_rank[u] > _rank[v])
			std::swap(u, v);
		// rank[u] <= rank[v] �� ������
		if (_rank[u] == _rank[v])
			_rank[v]++;
		_parent[u] = v;
	}
private:
	std::vector<int> _parent;
	std::vector<int> _rank;
};


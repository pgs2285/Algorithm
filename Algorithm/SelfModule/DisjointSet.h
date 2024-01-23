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
	// 조상을 찾음
	int Find(int u)
	{
		if (u == _parent[u])
		{
			return u;
		}
		return _parent[u] = Find(_parent[u]); // 최상위 부모밑으로 자식을 달아줌
	}

	void Merge(int u, int v)
	{
		u = Find(u);
		v = Find(v);

		if (u == v)
			return; // 최상위 부모가 같으면 그냥 return
		
		if (_rank[u] > _rank[v])
			std::swap(u, v);
		// rank[u] <= rank[v] 를 보장함
		if (_rank[u] == _rank[v])
			_rank[v]++;
		_parent[u] = v;
	}
private:
	std::vector<int> _parent;
	std::vector<int> _rank;
};


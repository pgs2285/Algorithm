#pragma once
struct Vertex
{
	
};
struct CostEdge
{
	int cost;

	int u;
	int v;
	bool operator<(CostEdge& other)
	{
		return cost < other.cost;
	}
};
class Kruskal
{
public:
	std::vector<CostEdge> selected;
	Kruskal(std::vector<Vertex> vertex, std::vector<std::vector<int>> adjacent)
		: _vertex(vertex), _adjacent(adjacent){}  
	int costSum();

private:
	std::vector<Vertex> _vertex;
	std::vector<std::vector<int>> _adjacent;
};


#pragma once
struct Vertex {
	int data;
};

class Dijkstra
{
public:
	Dijkstra(std::vector<Vertex> vertices, std::vector<std::vector<int>> adjacent);
	void findPath(int here);
private:
	std::vector<Vertex> _vertices;
	std::vector<std::vector<int>> _adjacent;

};


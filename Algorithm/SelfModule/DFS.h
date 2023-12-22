#pragma once
struct Vertex
{
	int data;
};

class DFS {
public:
	DFS(std::vector<Vertex> verteices, std::vector<std::vector<int>> adj);
	void visit(int here);
	void DfsEtc();

private:
	std::vector<Vertex> _verteices; // 정점 저장
	std::vector<std::vector<int>> adjacent; // 정점들의 관계 저장
	std::vector<bool> visited;
};
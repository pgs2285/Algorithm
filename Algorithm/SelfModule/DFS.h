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
	std::vector<Vertex> _verteices; // ���� ����
	std::vector<std::vector<int>> adjacent; // �������� ���� ����
	std::vector<bool> visited;
};
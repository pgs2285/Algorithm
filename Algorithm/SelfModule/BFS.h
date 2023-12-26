#pragma once

struct Vertex
{
	int data;
};

class BFS
{
public:
	BFS(std::vector<Vertex> verteices, std::vector<std::vector<int>> adj);
	void discover(int here);
	void discoverAll();
private:
	std::vector<Vertex> _vertexies;
	std::vector<bool> discovered;
	std::vector<std::vector<int>> adjacent;
public:
	std::vector<int> parent; // ���� �߰��߳�
	std::vector<int> distance; // ���������� �󸶳� ������ �ֳ�
};


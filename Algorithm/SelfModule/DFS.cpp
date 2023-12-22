#include <vector>
#include "DFS.h"
#include <iostream>


DFS::DFS(std::vector<Vertex> verteices, std::vector<std::vector<int>> adj)
{
	adjacent = adj;
	_verteices = verteices;
	visited = std::vector<bool>(_verteices.size(), false);
}

void DFS::visit(int here)
{

	visited[here] = true;
	std::cout << "Visited : " << here << std::endl;
	// 1. ���� �湮�� ���� ������ ������ ���
	for (int i = 0; i < adjacent[here].size(); i++)
	{
		int there = adjacent[here][i];
		if (visited[there] == false) // �湮���� �ʾҴٸ�.
		{
			visit(there);
		}
	}
}


void DFS::DfsEtc()
{
	for (int i = 0; i < _verteices.size(); i++)
	{
		
		if (visited[i] == false)
		{
			std::cout << "���� ��� ����" << std::endl;
			visit(i);
		}

	}
}


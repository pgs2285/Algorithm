#include <iostream>
#include <vector>
#include "SelfModule/Dijkstra.h"
using namespace std;
int main()
{
	std::vector<Vertex> vertices;
	vertices.resize(6);

	vector<vector<int>> adjacent = vector<vector<int>>(6, vector<int>(6, -1));
	adjacent[0][1] = 15; // 0->1
	adjacent[0][3] = 35;
	adjacent[1][0] = 15;
	adjacent[1][2] = 5;
	adjacent[1][3] = 10;
	adjacent[3][4] = 5;
	adjacent[5][4] = 5;

	Dijkstra d(vertices, adjacent);
	d.findPath(0);

}
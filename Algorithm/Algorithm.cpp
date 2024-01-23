#include <iostream>
#include <vector>
#include <thread>
#include "SelfModule/Kruskal.h"

using namespace std;

int main()
{
	vector<Vertex> vertices;
	vector<vector<int>> adjacent; // 인접행렬
	vertices.resize(6);
	adjacent = vector<vector<int>>(6, vector<int>(6, -1));
	//from - to
	adjacent[0][1] = adjacent[1][0] = 15;
	adjacent[0][3] = adjacent[3][0] = 35;
	adjacent[1][2] = adjacent[2][1] = 5;
	adjacent[1][3] = adjacent[3][1] = 10;
	adjacent[3][4] = adjacent[4][3] = 5;
	adjacent[3][5] = adjacent[5][3] = 10;
	adjacent[5][4] = adjacent[4][5] = 5;

	Kruskal kruskal(vertices, adjacent);
	cout << kruskal.costSum() << endl;


}
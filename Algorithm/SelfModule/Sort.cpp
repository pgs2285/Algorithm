#include <vector>
#include <iostream>
#include "Sort.h"

void Sort::BubbleSort()
{
	const int n = (int)v.size();
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < (n - 1 - i); j++)
		{
			if (v[j] > v[j + 1])
			{
				std::swap(v[j], v[j + 1]);
				
			}
			
		}
	}
}

void Sort::SelectionSort()
{
	const int n = (int)v.size();
	for (int i = 0; i < n - 1; i++)
	{
		int bestIdx = i;
		for (int j= i + 1; j < n; j++)
		{
			if (v[j] < v[bestIdx]) bestIdx = j;
		}
		std::swap(v[i], v[bestIdx]);
	}
}

void Sort::InsertSort()
{
	const int n = (int)v.size();
	for (int i = 1; i < n; i++)
	{
		int insertData = v[i];
		int j;
		for (j = i - 1; j >= 0; j--)
		{
			if (v[j] > insertData) v[j + 1] = v[j];
			else break; //밀어주다가 적당한 위치 찾으면 break
		}
		v[j + 1] = insertData; // 그 적당한 위칭 insertData
	}
}

void Sort::printV()
{
	for (int i = 0; i < v.size(); i++)
		std::cout << v[i] << " ";
	std::cout << std::endl;
}

#include <vector>
#include <iostream>
#include <queue>
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

void Sort::HeapSort()
{
	std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
	for (int num : v)
		pq.push(num);
	v.clear();
	while (pq.empty() == false)
	{
		v.push_back(pq.top());
		pq.pop();
	}
}

void Sort::MergeResult(int left, int mid, int right)
{
	//[1][3][5][9] | [2][4][6][10]  
	// 앞에꺼끼리 비교하고 작으면 결과벡터로 간다.

	std::vector<int> result;
	int leftIdx = left;
	int rightIdx = mid + 1;

	while (leftIdx <= mid && rightIdx <= right)
	{
		if (v[leftIdx] <= v[rightIdx])
		{
			result.push_back(v[leftIdx]);
			leftIdx++;
		}
		else
		{
			result.push_back(v[rightIdx]);
			rightIdx++;
		}
	}

	if (leftIdx > mid)
	{
		while (rightIdx <= right)
		{
			result.push_back(v[rightIdx]);
			rightIdx++;
		}
	}
	else
	{
		while (leftIdx <= mid)
		{
			result.push_back(v[leftIdx]);
			leftIdx++;
		}
	}
	for (int i = 0; i < result.size(); i++)
	{
		v[left + i] = result[i];
	}
}

void Sort::QuickSort(int left, int right)
{
	if (left > right) return;
	int pivot = partition(left,right);
	QuickSort(left, pivot - 1);
	QuickSort(pivot + 1, right);
}

int Sort::partition(int left, int right)
{
	int pivot = v[left];
	int low = left + 1;
	int high = right;

	while (low <= high)
	{
		while (low <= right && pivot >= v[low])
		{
			low++;
		}
		while (high >= left + 1 && pivot <= v[high] )
		{
			high--;
		}
		if (low < high)
		{
			std::swap(v[low], v[high]);
		}
	}
	std::swap(v[left], v[high]);

	return high;
}

void Sort::MergeSort(int left, int right)
{
	if (left >= right) 
		return;
	int mid = (left + right) / 2;
	MergeSort(left, mid);
	MergeSort(mid + 1, right);
	MergeResult(left,mid,right);
}

void Sort::printV()
{
	for (int i = 0; i < v.size(); i++)
		std::cout << v[i] << " ";
	std::cout << std::endl;
}

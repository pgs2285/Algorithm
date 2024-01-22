#pragma once

class Sort
{
public:
	Sort(std::vector<int>& nums) :v(nums)
	{
	}
	void BubbleSort();
	void printV();
	void SelectionSort();
	void InsertSort();
	void HeapSort();
	void MergeSort(int left, int right);  
	void MergeResult(int left, int mid, int right);
	void QuickSort(int left, int right);
	int partition(int left, int right);
private:
	std::vector<int> v;
};


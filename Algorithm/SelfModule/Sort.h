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
private:
	std::vector<int> v;
};


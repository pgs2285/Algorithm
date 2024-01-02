#pragma once
#include <vector>
template <typename T>
class BinarySearch
{

public:
	int binarySearch(std::vector<T> vec, int N);
private:
	std::vector<T> vec;
};

template<typename T>
inline int BinarySearch<T>::binarySearch(std::vector<T> vec, int N)
{
	int left = 0;
	int right = (int)vec.size() - 1;

	while (left <= right)
	{
		std::cout << "Å½»ö¹üÀ§ " << left << " ~ " << right << std::endl;
		int mid = (left + right) / 2;
		if (vec[mid] > N)
		{
			right = mid - 1;
		}
		else if (vec[mid] < N)
		{
			left = mid + 1;
		}
		else {

			return (left + right) / 2;
		}
	}
	
	return -1;
}

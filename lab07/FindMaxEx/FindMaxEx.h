#pragma once
#include <functional>
#include <vector>

template <typename T, typename Less = std::less<T>>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less = Less())
{
	if (arr.empty())
	{
		return false;
	}

	maxValue = arr[0];
	size_t arrSize = arr.size();
	for (size_t i = 1; i < arrSize; ++i)
	{
		if (less(maxValue, arr[i]))
		{
			maxValue = arr[i];
		}
	}
	return true;
}
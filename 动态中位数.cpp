#include <iostream>
#include <algorithm>
#include <vector>

#pragma warning(disable:4996)

using std::cin;
using std::cout;
using std::endl;

using std::make_heap;
using std::push_heap;
using std::pop_heap;
using std::sort_heap;
using std::less;
using std::greater;

using std::vector;

// #define GRPDEBUG


int main()
{
	// 助教说推荐使用scanf和printf，以节约时间
	int input(0), n(0);
	vector<int> maxHeap, minHeap;

	make_heap(maxHeap.begin(), maxHeap.end(), less<int>());
	make_heap(minHeap.begin(), minHeap.end(), greater<int>());



	while (scanf("%d", &input) == 1)
	{
		++n; // 计数当前的数据大小

#ifdef GRPDEBUG
		cout << "input" << input << endl;
#endif
		if (n == 1) // 对于第一个操作，默认放入min堆
		{
			minHeap.push_back(input);
			push_heap(minHeap.begin(), minHeap.end(), greater<int>());
		}

#ifdef GRPDEBUG
		for (const auto &x : maxHeap)
			cout << x << " ";
		cout << endl;
#endif
		else
		{
			if (input > minHeap[0]) // 此时应该放入最小堆
			{
				minHeap.push_back(input);
				push_heap(minHeap.begin(), minHeap.end(), greater<int>());
			}
			else // 放入最大堆
			{
				maxHeap.push_back(input);
				push_heap(maxHeap.begin(), maxHeap.end(), less<int>());
			}

			// 进行两个堆之间的调整

			if (maxHeap.size() > n / 2)
			{
				pop_heap(maxHeap.begin(), maxHeap.end(), less<int>());
				input = maxHeap.back();
				maxHeap.pop_back();
				minHeap.push_back(input);
				push_heap(minHeap.begin(), minHeap.end(), greater<int>());
			}

			else if (maxHeap.size() < n / 2)
			{
				pop_heap(minHeap.begin(), minHeap.end(), greater<int>());
				input = minHeap.back();
				minHeap.pop_back();
				maxHeap.push_back(input);
				push_heap(maxHeap.begin(), maxHeap.end(), less<int>());
			}
		}

		if (n % 2 == 1)
			printf("%d ", minHeap[0]);
		else
			printf("%d ", maxHeap[0]);
	}
	return 0;
}
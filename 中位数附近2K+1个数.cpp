#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <queue>

#include <climits>

using std::cout;
using std::cin;
using std::endl;

using std::vector;

using std::deque; //双向队列还是被弃用了，因为不能对中间的数据进行增减

using std::priority_queue;
using std::make_heap;
using std::less;
using std::greater;

using std::sort;
using std::swap;

int find_mid(vector<int> &list, int begin, int end, int size); //使用的是非迭代器
//通过递归的方法，采用快速中位数算法找到对应的中位数

int main()
{
	int k(0), n(0); //K是2K+1的标准，n是数串的长度

	int input(0);

	/*while (cin >> k >> n)
	{*/

	cin >> k >> n;
	vector<int> list;
	for (int i(0); i < n; ++i)
	{
		cin >> input;
		list.push_back(input);
	}
	//输入所需要的数串

	//vector<int> left, right;
	//make_heap(left.begin(), left.end(), less<int>());
	//make_heap(right.begin(), right.end(), greater<int>());

	//int i(0);
	//while(i < n)
	//{
	//	if ((!left.empty()) && (!right.empty())) //如果两个都已经是非空的了
	//	{
	//		
	//	}
	//}

	/*sort(list.begin(), list.end());

	int begin((n - 1) / 2 - k);

	for (int i(begin); i < begin + 2 * k + 1; ++i)
		cout << list[i] << " ";
	cout << endl;*/
	/*}*/


	int midnum = find_mid(list, 0, n - 1, n);
	/*for (auto c : list)
		cout << c << " ";
	cout << endl;*/
	//cout << midnum << endl;
	//经过验证，以中位数为划分，左右两部分分为了两个区域，左侧比中位数小，右侧反之
	
	//之后需要寻找K的前后部分
	for (int i(0); i < k; ++i) //需要寻找K次
	{
		int max = INT_MIN;
		int now_max_place(0);

		for (int j(0); j < n/2 - i; ++j)
		{
			if (list[j] > max)
			{
				max = list[j];
				now_max_place = j;
			}
		}
		swap(list[now_max_place], list[n / 2 - i - 1]);
	}

	for (int i(0); i < k; ++i)
	{
		int min = INT_MAX;
		int now_min_place(0);

		for (int j(n/2 + i + 1); j < n; ++j)
		{
			if (list[j] < min)
			{
				min = list[j];
				now_min_place = j;
			}
		}
		swap(list[now_min_place], list[n / 2 + i + 1]);
	}

	/*for (auto c : list)
		cout << c << " ";
	cout << endl;*/

	for (int i(n / 2- 1 + n%2 - k); i <= n / 2 + k -1 + n % 2; ++i)
		cout << list[i] << " ";
	cout << endl;

	return 0;
}

int find_mid(vector<int>& list, int begin, int end, int size)
{
	//进行快速中位数的寻找
	if (size == 1)
	{
		//如果此时只有一个长度的数串是有效的
		return list[0];
		//return 0;
	}

	//剩下的部分的长度是需要进行划分求解的

	int i(begin); //这里begin是key值
	int j(i + 1);
	for (; j <= end; ++j)
	{
		if (list[j] <= list[begin])
		{
			//此时的所指元素比头元素要小
			++i; //需要交换的元素是i递增之后的位置，这个元素期望的是比begin的元素大
			swap(list[i], list[j]);
		}
	}
	swap(list[begin], list[i]);


	//后面就要体现出递归的方法了

	if (i < size / 2 - 1 + size % 2) //进行数据修正
		return find_mid(list, i + 1, end, size);
	else if (i > size / 2 - 1 + size % 2)
		return find_mid(list, begin, i - 1, size);
	else
	{
		if (size % 2 == 1)
			return list[i];
			//return i;
		else
		{
			//int now_max = list[0];//需要寻求中位数的另一个基准
			//for (int ii(1); ii < i; ++ii)
			//{
			//	if (list[ii] > now_max)
			//		now_max = list[ii];

			//	return (list[i] + now_max) / 2;
			//	//return i;
			//}
			return list[i];
		}
	}
}

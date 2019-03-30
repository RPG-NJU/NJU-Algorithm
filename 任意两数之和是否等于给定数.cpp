/*
题目描述
给定一个 int 数组 arr，元素按照升序排列且各不相同。另外有一个目标数 c，请你找出 arr 中所有的数对 a, b，使得 a + b = c。

输入
输入为三行，第一行为 arr 的元素个数，第二行为 arr，元素以空格分隔，第三行为目标数 c。

输出
所有符合条件的数对 a, b。a 和 b 以空格分开，每个数对占据一行。每行中 a < b，所有数对以它的第一个数（也就是 a 的值）升序排列。


样例输入
9
-2 0 1 2 3 5 6 8 10 
8

样例输出
-2 10
0 8
2 6
3 5
*/

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

using std::vector;


int main()
{
	int n(0);
	int x(0); //作为目标数据

	cin >> n; //输入了数据的个数
	vector<int> list;

	int input(0);
	for (int i(0); i < n; ++i)
	{
		cin >> input;
		list.push_back(input);
	}
	cin >> x;

	for (int i(0); i < n; ++i)
	{
		for (int j(i + 1); j < n; ++j)
		{
			if (list[i] + list[j] == x)
			{
				cout << list[i] << " " << list[j] << endl;
			}
		}
	}
	return 0;
}

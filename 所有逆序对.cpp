/*
题目描述：
请大家在做oj题之前，仔细阅读关于抄袭的说明http://www.bigoh.net/JudgeOnline/.


给出一个字符串数组，如果（按照字典序）一个大的字符串在比它小的字符串前面我们称这两个字符串组成一个“逆序对”。你需要找到所有的逆序对的个数。

输入：
第一行是数组大小，第二行是以空格分隔的字符串数组.

注：预先知道每个字符串的长度都是 10.

输出：
所有的逆序对个数. 这次需要大家先输出一个字符串，它是“我已阅读关于抄袭的说明”的汉语拼音.输出此行的提交我们将认为已经完全阅读并了解了“关于抄袭的说明”公告.

注意：结果比较大，请用 long 类型保存.

样例输入：
3
aaaaaaaaaa cccccccccc bbbbbbbbbb

样例输出：
wo yi yue du guan yu chao xi de shuo ming
1

提示：
不要使用蛮力算法
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::sort;


// #define DEBUG_SHOW


// 长度的类型最好使用long long，因为数据可能会很大

long long ReversePair(vector<string> &list, int left, int right);

long long Merge(vector<string> &list, int left, int mid, int right);
// 需要将跨越中线的两个部分中的逆序对数量计算出来
// 同时重新归并成为升序排列的序列


int main()
{
	/*string a("apple"), b("banana");
	cout << (a < b) << endl;*/
	//对于string类型可以直接使用大于小于进行字典序判定

	/*
	 * 采取归并的方式进行求解
	 * 将一个序列从正中间分开，分为两个子问题求解
	 * 在两个序列中分别求出逆序对的个数，再将两个序列中跨序列的逆序对找出，进行合并求解
	 * 之后将两个序列合并排序，得到一个升序序列，方便下一次的求解
	 */

	

	int n(0);
	string input;
	vector<string> data;

	cin >> n;
	// 输入个数
	for (int i(0); i < n; ++i)
	{
		cin >> input;
		data.push_back(input);
	}
	// 完成了输入
	
#ifdef DEBUG_SHOW
	cout << "-----> INPUT ALL SHOW:" << endl;
	for (auto word : data)
		cout << word << " ";
	cout << endl;
#endif

	cout << "wo yi yue du guan yu chao xi de shuo ming" << endl;
	// 输出老师要求的特殊字符，我已阅读关于抄袭的说明

	cout << ReversePair(data, 0, n - 1) << endl;
	return 0;
}

long long ReversePair(vector<string>& list, int left, int right)
{
	if (left == right)
		return 0; // base-case

	// recursion-case
	long long mid = (left + right) / 2;

	long long left_recursion = ReversePair(list, left, mid);
	long long right_recursion = ReversePair(list, mid + 1, right);
	long long merge_result = Merge(list, left, mid, right);

	return left_recursion + merge_result + right_recursion;
}

long long Merge(vector<string>& list, int left, int mid, int right)
{
	// 用于将两个部分，合并计数，并且排序
	long long reverse_pair_count(0); // 用于计数
	long long i(left), j(mid + 1); // 作为遍历的两个指针

	for (; i <= mid && j <= right; )
	{
		if (list[i] > list[j])
		{
			reverse_pair_count += mid - i + 1;
			// 每次逆序元素，逆序对数量增加，m-i+1即为该元素到左序列尾的元素数量
			++j;
		}

		else
		{
			++i;
		}
	}

	sort(&list[left], &list[right] + 1);

	return reverse_pair_count;
}

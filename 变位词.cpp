/*
题目描述：
请大家在做oj题之前，仔细阅读关于抄袭的说明http://www.bigoh.net/JudgeOnline/.


变位词是指由相同的字母组成的单词，如eat、tea是变位词。本次问题给出一串单词，你需要找到所有的变位词。

输入：
输入由两行组成：第一行是所有单词的总数，第二行是由空格分隔的单词列表。两行末尾都有空格。

注：为防歧义，输入的单词都是小写

输出：
这次需要大家先输出一个字符串，它是“我已阅读关于抄袭的说明”的汉语拼音.输出此行的提交我们将认为已经完全阅读并了解了“关于抄袭的说明”公告.

第二行是变位词组的个数，后面是所有的变位词。每个输出的变位词占一行。一组变位词只需要输出一个字典序最小的代表即可，如eat、tea中eat字典序小于tea，所以输出eat。变位词与变位词也按照字典序从小到大排列，如eat和el中eat字典序小于el所以eat在el前面。

输出的每一行最后都没有空格。

样例输入：
9
a ew vc tea oe eat zoo el le 

样例输出：
wo yi yue du guan yu chao xi de shuo ming
2
eat
el

提示：
使用代价为O(nlgn)的方法。
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <complex>

using std::cout;
using std::cin;
using std::endl;
using std::ostream;

using std::string;
using std::vector;

using std::sort;
using std::min;


// #define GRPDEBUG

// 给出一些自测试的样例
/*

9
a ew vc tea oe eat zoo el le 

20 
tea for aet slu uls int shi ni ish hsi what for if it fi a his from a you 

*/

struct Word
{
	string original_word;
	string tag;
	int index;
};

ostream &operator<<(ostream &os, const Word &output);

void sort_by_original(vector<Word> &data);

bool compare_word(const Word &x, const Word &y);

void build_tag(vector<Word> &data);

void sort_by_tag(vector<Word> &data);

bool compare_tag(const Word &x, const Word &y);

void find_anagram(const vector<Word> &data, vector<string> &result);

int main()
{
	int n(0);
	vector<Word> data;
	vector<string> result;
	string input;

	cin >> n;
	for (int i(0); i < n; ++i)
	{
		cin >> input;
		Word x{ input, input, -1 };
		// data.push_back({ input, input, -1 });
		data.push_back(x);
	}
	// 完成了所有的输入

#ifdef GRPDEBUG
	cout << "[ALL INPUT SHOW]    ";
	for (const auto &x : data)
		cout << x << " ";
	cout << endl << endl;
#endif

	sort_by_original(data);

#ifdef GRPDEBUG
	cout << "[AFTER SORT BY WORD]    ";
	for (const auto &x : data)
		cout << x << " ";
	cout << endl << endl;
#endif

	build_tag(data);

#ifdef GRPDEBUG
	cout << "[AFTER BUILD TAG]    ";
	for (const auto &x : data)
		cout << x << " ";
	cout << endl << endl;
#endif

	sort_by_tag(data);

#ifdef GRPDEBUG
	cout << "[AFTER SORT BY TAG]    ";
	for (const auto &x : data)
		cout << x << " ";
	cout << endl << endl;
#endif

	find_anagram(data, result);

	cout << "wo yi yue du guan yu chao xi de shuo ming" << endl;
	// 按照助教的要求，输出“我已阅读关于抄袭的说明”



	const int length(result.size());
	cout << length << endl;
	// 输出易位词的对数

	if (length == 0)
	{
		
	}
	else
	{
		cout << result[0];
		for (int i(1); i < length; ++i)
			cout << endl << result[i];
	}


	return 0;
}

ostream& operator<<(ostream& os, const Word& output)
{
	os << "{" << output.original_word << " " << output.tag << " " << output.index << "}";
	return os;
}


void sort_by_original(vector<Word>& data)
{
	sort(data.begin(), data.end(), compare_word);

	// 需要更新index供后续进行操作
	const int length = data.size();
	for (int i(0); i < length; ++i)
		data[i].index = i;

	return;
}

bool compare_word(const Word& x, const Word& y)
{
	return x.original_word < y.original_word;
}

void build_tag(vector<Word>& data)
{
	//for (auto &x : data)
	//{
	//	sort(x.tag.begin(), x.tag.end());
	//}
	const int length(data.size());
	for (int i(0); i < length; ++i)
		sort(data[i].tag.begin(), data[i].tag.end());
	return;
}

void sort_by_tag(vector<Word>& data)
{
	sort(data.begin(), data.end(), compare_tag);

	return;
}

bool compare_tag(const Word& x, const Word& y)
{
	return x.tag < y.tag;
}

void find_anagram(const vector<Word>& data, vector<string>& result)
{
	const int length(data.size());

	if (length == 1 || length == 0)
		return;
	// 个人认为不会出现的特殊情况，但是还是进行了讨论

	else
	{
		int min_index(INT32_MAX);
		int real_index(-1);
		for (int i(1), j(0); i < length; ++i, ++j)
		{
			if (data[i].tag == data[j].tag)// 此时就存在了易位词
			{
				if (min_index == INT32_MAX)
				{
					min_index = min(data[i].index, data[j].index);
					if (data[i].index > data[j].index)
						real_index = j;
					else
						real_index = i;
				}
				else
				{
					const int old_min = min_index;
					min_index = min(data[i].index, min_index);
					if (data[i].index < old_min)
						real_index = i;
				}
#ifdef GRPDEBUG
				cout << "(" << data[i].tag << ") in " << min_index << endl;
				cout << (i == length - 1) << endl;
#endif
				if (i == length - 1)
					goto special;
			}

			else
			{
				special:
				if (min_index == INT32_MAX)
					continue;
				else
				{
					result.push_back(data[real_index].original_word);
#ifdef GRPDEBUG
					cout << "[" << real_index << "] is " << data[real_index].original_word << endl;
#endif
					min_index = INT32_MAX;
				}
			}
		}
	}

	sort(result.begin(), result.end());

	return;
}

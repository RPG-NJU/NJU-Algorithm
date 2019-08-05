#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>


using std::cin;
using std::cout;
using std::endl;

using std::stringstream;
using std::string;
using std::vector;

using std::getline;
using std::min;
using std::swap;

struct Node
{
	int child_num;
	int child[2];
};
struct YesNo
{
	int yes;
	int no;
};

int MinPointCover(const vector<vector<int> >& data, vector<YesNo>& dp);

vector<vector<int> > data;

int main()
{
	string input;
	// vector<vector<int> > data;


	while (getline(cin, input))
	{
		vector<int> this_line; // (3, -1);
		// int i(0);
		int a_long;
		stringstream input_stream(input);
		while (input_stream >> a_long)
		{
			this_line.push_back(a_long);
			// this_line[i] = a_long;
			// ++i;
		}

		data.push_back(this_line);
	}

	// cout << sizeof(data) << endl;
	//for (int i(0); i < data.size(); ++i)
	//{
	//	for (int j(0); j < data.size() - 1; ++j)
	//	{
	//		if (data[j][0] > data[j + 1][0])
	//			swap(data[j], data[j + 1]);
	//	}
	//}

	// vector<Node> nodes; //  (data.size(), { 0, {-1, -1} });
	// vector<vector<int> > dp(data.size(), *(new vector<int>(2, 0)));
	vector<YesNo> dp(data.size(), { 0,0 });
	//for (int i(0); i < data.size(); ++i)
	//{
	//	Node this_node{ 0, {-1, -1} };
	//	this_node.child_num = data[i].size() - 1;
	//	for (int j(1); j < data[i].size(); ++j)
	//	{
	//		this_node.child[j - 1] = data[i][j];
	//		// this_node.child_num++;
	//		// cout << i << " " << this_node.child_num << endl;
	//	}

	//	nodes.push_back(this_node);
	//}

	cout << "I have read the rules about plagiarism punishment" << endl;
	cout << MinPointCover(data, dp) << endl;

	return 0;
}

int MinPointCover(const vector<vector<int> >& data, vector<YesNo>& dp)
{
	for (int i(data.size() - 1); i >= 0; --i)
	{
		// cout << "?" << endl;
		if (data.size() <= 1)
		{
			dp[i].no = 0;
			dp[i].yes = 1; // base case
			// cout << "?" << endl;
			// cout << i << ":" << dp[i][0] << 
		}
		else
		{
			for (int j(1); j < data[i].size(); ++j)
			{
				// cout << j << endl;
				// cout << i << " " << nodes[i].child_num << endl;
				dp[i].no += dp[data[i][j]].yes;
				dp[i].yes += min(dp[data[i][j]].yes, dp[data[i][j]].no);
				// cout << i << ":" << dp[i][0] << " " << dp[i][1] << endl;
			}
			dp[i].yes++;
		}
	}

	return min(dp[0].yes, dp[0].no);
}

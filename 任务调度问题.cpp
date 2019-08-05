#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

using std::cin;
using std::cout;
using std::endl;

using std::sort;
using std::min;
using std::max;

enum COLOR{white, gray, black};

void critical_path(int node, vector<int> &est, vector<int>& eft, vector<int> &CritDep, vector<COLOR> &color, const vector<vector<int> > &edge, const vector<int> &task_time);


int main()
{
	int n(0), task(0), t_time(0);
	int x(0), y(0);
	

	cin >> n;
	vector<int> task_time(n, 0);
	vector<vector<int> > edge;
	vector<vector<int> > none_use_edge;
	vector<int> est(n, 0);
	vector<int> CritDep(n, 0);
	vector<COLOR> color(n, white);
	vector<int> eft(n, 0);

	for (int i(0); i < n; ++i)
	{
		edge.push_back(*(new vector<int>));
		none_use_edge.push_back(*(new vector<int>));
	}
	
	for (int i(0); i < n; ++i)
	{
		cin >> task >> t_time;
		task_time[task - 1] = t_time; // ¶ÔÓ¦Î»ÖÃ
	}

	while (cin >> x >> y)
	{
		edge[y - 1].push_back(x - 1);
		none_use_edge[x - 1].push_back(y - 1);
	}


	cout << "I have read the rules about plagiarism punishment" << endl;

	int result(0);

	for (int i(0); i < n; ++i)
	{
		if (none_use_edge[i].size() == 0)
		{
			critical_path(i, est, eft, CritDep, color, edge, task_time);
		}
		int j(0);
		for (; j < n; ++j)
		{
			if (color[j] == white)
				break;
		}

		if (j == n)
			break;
	}
	for (int i(0); i < n; ++i)
	{
		result = max(result, eft[i]);
	}
	cout << result;

	return 0;
}

void critical_path(int node, vector<int>& est, vector<int>& eft, vector<int>& CritDep, vector<COLOR>& color, const vector<vector<int> >& edge, const vector<int>& task_time)
{
	color[node] = gray;
	est[node] = 0;
	CritDep[node] = -1;

	for (int i(0); i < edge[node].size(); ++i)
	{
		int w = edge[node][i];

		if (color[w] == white)
		{
			critical_path(w, est, eft, CritDep, color, edge, task_time);
			if (eft[w] >= est[node])
			{
				est[node] = eft[w];
				CritDep[node] = w;
			}
		}
		else
		{
			if (eft[w] >= est[node])
			{
				est[node] = eft[w];
				CritDep[node] = w;
			}
		}
	}

	eft[node] = est[node] + task_time[node];
	color[node] = black;
	return;
}

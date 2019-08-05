#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;

using std::vector;

using std::sort;
using std::min;
using std::max;
using std::swap;

// 实验采用DFS框架完成
enum COLOR { white, gray, black };

struct Node
{
	int discover; // 被发现时间
	int back; // 不通过父节点能够访问到的祖先的最小时间戳
	int parent; // 父节点
	COLOR color;
};

struct Edge
{
	int v;
	int w;
};

void show_data(const vector<vector<int> >& data);
int DFS(int x, vector<Node>& node, const vector<vector<int> >& data);
void show_node(const vector<Node>& node);

int t(0);
vector<int> articulation_point;
vector<Edge> bridge;

int main()
{
	vector<Node> node;
	vector<vector<int> > data;


	int n(0), x(0), y(0);

	cin >> n;
	for (int i(0); i < n; ++i)
	{
		data.push_back(*(new vector<int>));
		Node x{ 0,0,0, white };
		node.push_back(x);
	}

	while (cin >> x >> y)
	{
		data[x].push_back(y);
		data[y].push_back(x);
	}

	// show_data(data);
	// 正确性已经得到了验证

	DFS(0, node, data);
	int root_time(0);
	for (int i(0); i < node.size(); ++i)
	{
		if (node[i].parent == 0)
			++root_time;
	}
	if (root_time == 1)
		articulation_point.push_back(0);
	sort(articulation_point.begin(), articulation_point.end());

	for (int i(0); i < bridge.size(); ++i)
	{
		for (int j(0); j < bridge.size() - 1; ++j)
		{
			if (bridge[j].v > bridge[j + 1].v)
				swap(bridge[j], bridge[j + 1]);
		}
	}

	cout << "wo yi yue du guan yu chao xi de shuo ming" << endl;
	for (int i(0); i < articulation_point.size(); ++i)
		cout << articulation_point[i] << endl;
	for (int i(0); i < bridge.size(); ++i)
	{
		cout << bridge[i].v << " " << bridge[i].w << endl;
	}
	return 0;
}

void show_data(const vector<vector<int>> & data)
{
	for (int i(0); i < data.size(); ++i)
	{
		cout << i << " : ";
		for (int j(0); j < data[i].size(); ++j)
			cout << data[i][j] << " ";
		cout << endl;
	}

	return;
}

int DFS(int x, vector<Node> & node, const vector<vector<int>> & data)
{
	node[x].color = gray;
	++t;
	node[x].discover = t;
	node[x].back = t;

	// show_node(node);
	for (int i(0); i < data[x].size(); ++i)
	{
		if (node[data[x][i]].color == white)
		{
			node[data[x][i]].parent = x;
			// cout << x << "->" << data[x][i] << endl;
			node[data[x][i]].back = DFS(data[x][i], node, data);
			if (node[data[x][i]].back >= node[x].discover && x != 0)
			{
				// cout << "output" << " " << x << endl;
				// show_node(node);
				articulation_point.push_back(x);
			}
			node[x].back = min(node[x].back, node[data[x][i]].back);
			if (node[x].discover < node[data[x][i]].back)
			{
				Edge e{ min(x, data[x][i]), max(x, data[x][i]) };
				bridge.push_back(e);
			}
		}
		else
		{
			if (node[x].parent != data[x][i])
			{
				// cout << x << " back to " << data[x][i] << endl;
				node[x].back = min(node[data[x][i]].discover, node[x].back);
			}
		}
	}

	return node[x].back;
}

void show_node(const vector<Node>& node)
{
	for (int i(0); i < node.size(); ++i)
	{
		cout << i << " discover:" << node[i].discover << " back:" << node[i].back << endl;
	}

	return;
}

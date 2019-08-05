#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <queue>

using std::cin;
using std::cout;
using std::endl;

using std::getline;

using std::vector;
using std::string;
using std::queue;

using std::stringstream;

using std::swap;


enum COLOR {WHITE, GRAY, BLACK};
enum TWO_COLOR {NONE, RED, BLUE};



void show_edge(const vector<vector<int> >& edge);
void BFS_and_TWOPART(const vector<vector<int> >& edge, vector<COLOR>& color, vector<TWO_COLOR>& two_color);

int main()
{
	
	string input;
	vector<vector<int> > edge;
	vector<COLOR> color;
	vector<TWO_COLOR> two_color;
	
	while (getline(cin, input))
	{
		vector<int> this_line;
		int point;
		stringstream input_stream(input);
		while (input_stream >> point)
		{
			this_line.push_back(point);
		}

		edge.push_back(this_line);
	}

	for (int i(0); i < edge.size(); ++i)
	{
		for (int j(0); j < edge.size() - 1; ++j)
		{
			if (edge[j][0] > edge[j + 1][0])
				swap(edge[j], edge[j + 1]);
		}
	}

	for (int i(0); i < edge.size(); ++i)
	{
		color.push_back(WHITE);
		two_color.push_back(NONE);
	}
	// show_edge(edge);

	BFS_and_TWOPART(edge, color, two_color);

	cout << "wo yi yue du guan yu chao xi de shuo ming" << endl;

	for (int i(0); i < edge.size(); ++i)
	{
		if (two_color[i] == RED)
			cout << i << endl;
	}

	return 0;
}

void show_edge(const vector<vector<int>>& edge)
{
	for (int i(0); i < edge.size(); ++i)
	{
		for (int j(0); j < edge[i].size(); ++j)
		{
			cout << edge[i][j] << " ";
		}
		cout << endl;
	}
	return;
}

void BFS_and_TWOPART(const vector<vector<int>>& edge, vector<COLOR>& color, vector<TWO_COLOR>& two_color)
{
	queue<int> points;
	points.push(0); // 从节点零开始进行遍历
	color[0] = GRAY;
	two_color[0] = RED; // 从RED开始进行染色

	while(!points.empty())
	{
		// 当队列非空
		int s(points.front());
		for (int i(1); i < edge[s].size(); ++i) // 对于所有与s相连的节点
		{
			if (color[edge[s][i]] == WHITE)
			{
				points.push(edge[s][i]);
				color[edge[s][i]] = GRAY;

				two_color[s] == RED ? two_color[edge[s][i]] = BLUE : two_color[edge[s][i]] = RED;
			}
		}
		points.pop();
		color[s] = BLACK;
	}


	return;
}

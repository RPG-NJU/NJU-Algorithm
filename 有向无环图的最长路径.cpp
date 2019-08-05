#include<iostream>
#include<sstream>
#include<vector>
#include<string>
#include<algorithm>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)


using std::cin;
using std::cout;
using std::endl;
using std::getline;

using std::min;
using std::max;
using std::swap;

using std::string;
using std::vector;


struct Edge
{
	// int src;
	int dest;
	int weight;
};



enum COLOR{WHITE, GRAY, BLACK};

struct Node
{
	int discover;
	int back;
	COLOR color;
};

void DFS_TopSort(const vector<vector<Edge> > &edges, vector<Node> &nodes, vector<int> &stack, int v);
void DistanceCompute(const vector<vector<Edge> >& edges, vector<int>& stack, vector<int>& distance);

int main()
{
	int n(0);
	cin >> n; // input points num

	vector<vector<Edge> > edges(n, *(new vector<Edge>)); // init edges vector
	int src, dest, weight;
	while (scanf("%d %d %d", &src, &dest, &weight) != EOF) // loop to input
	{
		Edge edge;
		edge.dest = dest;
		edge.weight = weight;
		edges[src].push_back(edge); // 构建带权邻接表
	}
	vector<int> distance(n, INT16_MIN); // 全部初始化为-∞
	Node init_node{ -1, -1, WHITE };
	vector<Node> nodes(n, init_node); // init nodes
	vector<int> stack;

	DFS_TopSort(edges, nodes, stack, 0);
	// cout << stack.back() << endl;
	DistanceCompute(edges, stack, distance);
	
	cout << "I have read the rules about plagiarism punishment" << endl;
	for (int i(1); i < distance.size(); ++i)
	{
		cout << distance[i] << " ";
	}

	return 0;
}

void DFS_TopSort(const vector<vector<Edge>>& edges, vector<Node>& nodes, vector<int>& stack, int v)
{
	nodes[v].color = GRAY;
	for (int i(0); i < edges[v].size(); ++i)
	{
		int w(edges[v][i].dest); // 从邻接表中找到节点
		if (nodes[w].color == WHITE)
		{
			DFS_TopSort(edges, nodes, stack, w);
		}
	}
	nodes[v].color = BLACK;
	stack.push_back(v);


	return;
}

void DistanceCompute(const vector<vector<Edge>>& edges, vector<int>& stack, vector<int>& distance)
{
	distance[0] = 0;

	// stack.pop_back();

	while(!stack.empty())
	{
		// cout << "?" << endl;
		int v(stack.back());
		for (int i(0); i < edges[v].size(); ++i)
		{
			
			int w(edges[v][i].dest);
			// cout << i << " " << edges.size() << endl;
			distance[w] = max(distance[w], distance[v] + edges[v][i].weight);
		}
		stack.pop_back();
	}

	return;
}

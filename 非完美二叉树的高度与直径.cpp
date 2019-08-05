#include <iostream>
#include <vector>
#include <algorithm>


using std::cin;
using std::cout;
using std::endl;

using std::vector;

using std::max;

int tree_height(vector<int> &preorder, vector<int> &inorder, int in_begin, int in_end, int pre_root, int &d); // root为前序中的根的表示位置


// int tree_d();
// 如果是两个函数的方式来完成的话，会有重复的计算，因为直径其实与高度有很大的关系
// 从数学关系上来看，最大的直径应该为左右子树的高度+2（因为需要跨过根节点连接起来两个子树的最远叶节点）

int main()
{
	int n(0);
	vector<int> preorder, inorder;
	int input(0);
	int height(0), d(0);

	// 如果采用分治算法，应该是分解为左右子树进行递归求解

	cin >> n; // 输入数据量

	for (int i(0); i < n; ++i)
	{
		cin >> input;
		preorder.push_back(input);
	}
	for (int i(0); i < n; ++i)
	{
		cin >> input;
		inorder.push_back(input);
	}

	height = tree_height(preorder, inorder, 0, n - 1, 0, d);

	cout << "I have read the rules about plagiarism punishment" << endl;
	cout << height << endl;
	cout << d ;// << endl;
	return 0;
}


int tree_height(vector<int>& preorder, vector<int> &inorder, int in_begin, int in_end, int pre_root, int &d)
{
	// 首先需要确定是否是base-case
	if (in_begin == in_end) // 此时是子树只有根节点，而不具有叶节点
	{
		d = 0; // 此时直径应该是0
		return 0; // 此时的高度也是0
	}

	else if (in_begin > in_end) // 这种情况的导致描述起来比较玄学，有可能是某一个节点的一侧子树是为空的，但是经过计算之后断然会得到一个“子树”，但是“子树”是虚无的，虚无的体现就在于，左右的边界是不合理的，所以此处最终得到的高度应该是0，为了保持一致，所返回-1，最终+1之后得到0
	{
		d = 0;
		return -1;
	}

	int root_in_inorder(0);
	// 对于前序遍历而言，子树的根应该是存在于序列头的
	int ld(d), rd(d);
	int left_height(0), right_height(0);

	// P.S. 曾经以为不需要root变量来控制根的位置，但是其实前序和中序所截取的部分是不一样的，所以需要两组变量来控制所截取的部分，其中，前序遍历中只需要关注根节点的位置就好了

	for (int i(in_begin); i <= in_end; ++i)
	{
		if (inorder[i] == preorder[pre_root]) // 在中序遍历中找到前序遍历根节点所指向的元素，作为分割，分割成为左右子树
		{
			root_in_inorder = i; // 在中序序列中，这次的分割将树分成了，[in_begin , root_in_inorder - 1]左子树 和 [root_in_inorder + 1 , in_end]右子树 两个部分
			break; // break
		}
	}

	// 这里需要进行一次数理的分析，需要找到对应的前序序列的标志点——pre_root的新值

	/*
	 * 我们得到的所有信息如下：
	 * 中序遍历中： [in_begin , root_in_inorder - 1]左子树 和 [root_in_inorder + 1 , in_end]右子树
	 * 前序遍历中： 两个子树的父节点为 pre_root
	 * 所以可以分析得到：
	 * 左子树的根节点应该为 pre_root + 1
	 * 右子树的根节点计算会比较繁琐，需要越过所有的左子树，所以可以计算，左子树的大小为：root_in_inorder - 1 - in_begin + 1 = root_in_inorder - in_begin，需要越过左子树，为 pre_root + root_in_inorder - in_begin + 1
	 */

	left_height = tree_height(preorder, inorder, in_begin, root_in_inorder - 1, pre_root + 1, ld);
	right_height = tree_height(preorder, inorder, root_in_inorder + 1, in_end, pre_root + root_in_inorder - in_begin + 1, rd);

	d = max(ld, rd); // 在两个返回值中找到最大的一个
	if (left_height + right_height + 2 > d)
		d = left_height + right_height + 2;

	return max(right_height, left_height) + 1;
}

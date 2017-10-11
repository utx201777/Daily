#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

int dimUsed;

// kd树的节点定义
struct KdNode
{
	KdNode * parent;
	KdNode * leftChild;
	KdNode * rightChild;
	vector<int> val;	//存储的数据
	int axis;		// 使用的轴
	KdNode(vector<int> data, int ax)
	{
		val = data;
		axis = ax;
		parent = NULL;
		leftChild = NULL;
		rightChild = NULL;
	}
};

// 用于以第n位进行比较，方便重载
bool cmp(vector<int> a, vector<int> b)
{
	if (a[dimUsed] < b[dimUsed])
		return true;
	return false;
}

ostream & operator<<(ostream & os, vector<int> vi)
{
	os << "(";
	for (int i = 0; i < vi.size(); i++)
		cout << vi[i] << ",";
	os << ")";
	return os;
}

// 导入数据，第一行是数据数量和维度，后面跟着num行dim维度的数据，每个一行
bool loadData(string filename, vector<vector<int> > &data)
{
	ifstream infs(filename);
	if (infs.is_open())
	{
		int num,dim;
		infs >> num>>dim;
		vector<int> d(dim);
		for (int i = 0; i < num; i++)
		{
			for (int j = 0; j < dim; j++)
				infs >> d[j];
			data.push_back(d);
		}
		return true;
	}
	return false;
}

// 计算N维向量距离
int disVector(vector<int> a, vector<int> b)
{
	int sum = 0;
	for (int i = 0; i < a.size(); i++)
		sum += (a[i] - b[i])*(a[i] - b[i]);
	return sum;
}

class KdTree
{
private:
	int dimension;
	vector<vector<int> > data;
	KdNode * root;
public:
	KdTree(vector<vector<int> > d, int dim)
	{
		dimension = dim;
		data = d;
	}
	void createTree()
	{
		// 递归建树
		root = createTreeNode(0, data.size()-1,0);
	}

	// create Kd Tree struct
	KdNode * createTreeNode(int left, int right,int dim)
	{
		if (right < left)
			return NULL;
		dimUsed = dim;
		// 按照k维进行排序
		sort(data.begin() + left, data.begin() + right+1, cmp);
		int mid = (left + right+1) / 2;
		KdNode * r = new KdNode(data[mid], dim);
		r->leftChild = createTreeNode(left, mid - 1, (dim + 1) % dimension);
		if (r->leftChild != NULL)
			r->leftChild->parent = r;
		r->rightChild = createTreeNode(mid + 1, right, (dim + 1) % dimension);
		if (r->rightChild != NULL)
			r->rightChild->parent = r;
		return r;
	}

	void printKdTree()
	{
		printKdTreeNode(root);
	}

	void printKdTreeNode(KdNode * r)
	{
		if (r == NULL)
			return;
		printKdTreeNode(r->leftChild);
		cout << r->val << "\t";
		printKdTreeNode(r->rightChild);
	}

	// 查找kd树
	KdNode * searchKdTree(vector<int> d)
	{
		int dim = 0,minDis = 10000000;
		KdNode * r = root;
		KdNode * tmp;
		while (r != NULL)
		{
			tmp = r;
			if (d[dim] < r->val[dim])							
				r = r->leftChild;	
			else
				r = r->rightChild;
			dim = (dim + 1) % dimension;
		}
		// 找到属于的那个节点
		minDis = min(disVector(d, tmp->val),minDis);
		KdNode * nearNode = tmp;
		cout << endl<<"nearest node: "<<tmp->val << endl;
		// 退回到根节点
		while (tmp->parent != NULL)
		{
			tmp = tmp->parent;
			// 判断父节点是否更近，如果近，更新最近节点
			if (disVector(tmp->val, d) < minDis)
			{
				nearNode = tmp;
				minDis = disVector(tmp->val, d);
			}
			cout << "now parent node: " << tmp->val << endl;
			KdNode * son;
			// 判断当前轴与点的距离，如果小于minDis，则进行到另一半进行查找
			if (abs(tmp->val[tmp->axis] - d[tmp->axis]) < minDis)
			{
				if (tmp->val[tmp->axis] > d[tmp->axis])
					son = tmp->rightChild;
				else
					son = tmp->leftChild;
				searchKdTreeNode(d, minDis, nearNode, son);
			}
		}	
		// 对根节点的另外半边子树进行搜索
		/*if (abs(tmp->val[tmp->axis] - d[tmp->axis]) < minDis)
		{
			if (tmp->val[tmp->axis] > d[tmp->axis])
				tmp = tmp->rightChild;
			else
				tmp = tmp->leftChild;
			searchKdTreeNode(d, minDis, nearNode, tmp);
		}*/
		return nearNode;
	}

	// 查找当前节点下的最近点
	void searchKdTreeNode(vector<int> d,int &minDis,KdNode * &nearNode,KdNode * tmp)
	{
		// 递归终止
		if (tmp == NULL)
			return;
		cout << "now node: " << tmp->val << endl;
		// 判断当前节点是否小于
		if (disVector(tmp->val, d) < minDis)
		{
			minDis = disVector(tmp->val, d);
			nearNode = tmp;
		}
		// 如果轴与节点的距离小于minDis，则两个半边都需要搜索，否则只需要搜索一个半边
		if (abs(tmp->val[tmp->axis] - d[tmp->axis]) < minDis)
		{
			searchKdTreeNode(d, minDis, nearNode, tmp->leftChild);
			searchKdTreeNode(d, minDis, nearNode, tmp->rightChild);
		}
		else
		{
		// 选择搜索的一个半边
			if (tmp->val[tmp->axis] > d[tmp->axis])
				searchKdTreeNode(d, minDis, nearNode, tmp->leftChild);
			else
				searchKdTreeNode(d, minDis, nearNode, tmp->rightChild);
		}
		
	}

};

// 测试kd树
void testKdTree()
{
	vector<vector<int> > data;
	loadData("kd.txt", data);
	KdTree * kdtree = new KdTree(data, data[0].size());
	kdtree->createTree();
	kdtree->printKdTree();
	cout << endl;
	vector<int> vi(2);
	cin >> vi[0] >> vi[1];
	KdNode * r = kdtree->searchKdTree(vi);
	cout << r->val << endl;
}
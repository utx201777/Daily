#ifndef _GMM_H
#define _GMM_H
#include <vector>
#include <cmath>
using namespace std;
class GMM
{
public:
	void Init(const vector<double> &inputData, const int clustNum = 5, double eps = 0.01, double max_steps = 20);
	void train();
	int predicate(double x);//预测输入的数据属于哪一类
	void print();
protected:
	int clusterNum;				// 限制
	vector<double> means;
	vector<double> means_bkp;		// 上一次的迭代数据
	vector<double> sigmas;
	vector<double> sigmas_bkp;		// 上一次的迭代数据
	vector<double> probilities;
	vector<double> probilities_bkp;
	vector<vector<double>> memberships;		// 存储属于哪一个类别
	vector<vector<double>> memberships_bkp;
	vector<double> data;
	int dataNum;		// 数据数量
	double epslon;		// 相差的阈值
	double max_steps;	// 迭代次数
private:
	double gauss(const double x, const double m, const double sigma);
};
#endif

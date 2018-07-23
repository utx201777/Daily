#include "GMM.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <Windows.h>
using namespace std;

void GMM::Init(const vector<double> &inputData, const int clustNum, double eps, double max_steps)
{
	/*获取输入数据*/
	this->data = inputData;
	this->dataNum = data.size();
	/*存储最终需要的结果*/
	this->clusterNum = clustNum;		// 聚类数量
	this->epslon = eps;					// 阈值
	this->max_steps = max_steps;		// 最大的迭代次数
	/*保留每一个类别的均值，方差参数，保留上一个的参数*/
	this->means.resize(clusterNum);
	this->means_bkp.resize(clusterNum);
	this->sigmas.resize(clusterNum);
	this->sigmas_bkp.resize(clusterNum);
	/*保留每一个数据对于每一个类别下的概率，由在这个类别下的概率除以到各个类别的总概率得到*/
	this->memberships.resize(clusterNum);
	this->memberships_bkp.resize(clusterNum);
	for (int i = 0; i < clusterNum; i++)
	{
		memberships[i].resize(data.size());
		memberships_bkp[i].resize(data.size());
	}
	/*每一个类别的可能性*/
	this->probilities.resize(clusterNum);
	this->probilities_bkp.resize(clusterNum);
	//initialize mixture probabilities 初始化每个类别的参数
	for (int i = 0; i < clusterNum; i++)
	{
		probilities[i] = probilities_bkp[i] = 1.0 / (double)clusterNum;
		//init means
		means[i] = means_bkp[i] = 255.0*i / (clusterNum);
		//init sigma
		sigmas[i] = sigmas_bkp[i] = 50;
	}
}

void GMM::train()
{
	//compute membership probabilities
	int i, j, k, m;
	double sum = 0, sum2;
	int steps = 0;
	bool go_on;
	do			// 迭代
	{
		for (k = 0; k < clusterNum; k++)
		{
			//compute membership probabilities
			for (j = 0; j < data.size(); j++)
			{
				//计算p(k|n)，计算每一个数据在每一个类别的值的加权和
				sum = 0;
				for (m = 0; m < clusterNum; m++)
				{
					sum += probilities[m] * gauss(data[j], means[m], sigmas[m]);
				}
				//求分子，第j个数据在第k类中的所占的比例
				memberships[k][j] = probilities[k] * gauss(data[j], means[k], sigmas[k]) / sum;
			}
			//求均值
			//求条件概率的和，将每个数据在第k类中的概率进行累加
			sum = 0;
			for (i = 0; i < dataNum; i++)
			{
				sum += memberships[k][i];
			}
			//得到每个数据在属于第k类的加权值之和
			sum2 = 0;
			for (j = 0; j < dataNum; j++)
			{
				sum2 += memberships[k][j] * data[j];
			}
			//得到新的均值 由概率加权和除以总概率作为均值
			means[k] = sum2 / sum;
			//求方差  由到均值的平方的加权和作为新的方差
			sum2 = 0;
			for (j = 0; j < dataNum; j++)
			{
				sum2 += memberships[k][j] * (data[j] - means[k])*(data[j] - means[k]);
			}
			sigmas[k] = sqrt(sum2 / sum);
			//求概率
			probilities[k] = sum / dataNum;
		}//end for k
		//check improvement
		go_on = false;
		for (k = 0; k<clusterNum; k++)
		{
			if (means[k] - means_bkp[k]>epslon)
			{
				go_on = true;
				break;
			}
		}
		//back up
		this->means_bkp = means;
		this->sigmas_bkp = sigmas;
		this->probilities_bkp = probilities;
	} while (go_on&&steps++ < max_steps); //end do while
}

double GMM::gauss(const double x, const double m, const double sigma)
{
	return 1.0 / (sqrt(2 * 3.1415926)*sigma)*exp(-0.5*(x - m)*(x - m) / (sigma*sigma));
}
int GMM::predicate(double x)
{
	double max_p = -100;
	int i;
	double current_p;
	int bestIdx = 0;
	for (i = 0; i < clusterNum; i++)
	{
		current_p = gauss(x, means[i], sigmas[i]);
		if (current_p > max_p)
		{
			max_p = current_p;
			bestIdx = i;
		}
	}
	return bestIdx;
}
void GMM::print()
{
	int i;
	for (i = 0; i < clusterNum; i++)
	{
		cout << "Mean: " << means[i] << " Sigma: " << sigmas[i] << " Mixture Probability: " << probilities[i] << endl;
	}
}
//void mainxx()
//{
//    GMM gmm;
//    gmm.test();
//}
//void GMM::test()
//{
//    //test guass
//    for (int j=0;j<10;j++)
//    {
//        cout<<gauss(j,0,1)<<endl;
//    }
//    srand(GetTickCount());
//    vector<double> datas;
//    int i;
//    double d;
//    for (i=0;i<20;i++)
//    {
//        d=(rand()/(double)RAND_MAX)*255;
//        cout<<d<<endl;
//        datas.push_back(d);
//    }
//    this->Init(datas,2);
//    this->train();
//    this->predicate(100);
//}
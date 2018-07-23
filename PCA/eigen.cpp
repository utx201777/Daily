// PCA Eigen实现

// 原始数据
MatrixXf m(point_cnt, 3);
// 计算协方差矩阵
    Matrix3f cov_matrix;
    for(int i=0;i<3;++i)
        for (int j = 0; j < 3; ++j)
        {           
            VectorXf v1 = m.col(i);
            VectorXf v2 = m.col(j);
            float mean_1 = v1.mean();
            float mean_2 = v2.mean();           
            for (int k = 0; k < v1.size(); ++k)
            {
                v1[k] -= mean_1;
                v2[k] -= mean_2;
            }           
            float sum = v1.dot(v2);
            sum /= 9;
            cov_matrix(i, j) = cov_matrix(j, i) = sum;
        }       

    // 获得特征值和特征向量
    EigenSolver<Matrix3f> es(cov_matrix);
    Vector3f D = es.pseudoEigenvalueMatrix().diagonal();// 特征值
    Matrix3f V = es.pseudoEigenvectors();    // 特征向量
    // 以下过程按照特征值对特征向量进行排序
    vector<pair<int, float>> eigen_value_index;
    for (int i = 0; i < 3; ++i)
        eigen_value_index.push_back(make_pair(i,D[i]));
    auto f = [](pair<int, float> &a, pair<int, float>&b)->bool {return a.second > b.second;  };
    sort(eigen_value_index.begin(), eigen_value_index.end(), f);               // 按照特征值对特征向量进行排序
    Matrix3f tranform_matrix;
    for (int i = 0; i < 3; ++i)
    {
        int idx = eigen_value_index[i].first;
        tranform_matrix.col(i) = V.col(idx);
    }   

    // 变换后的结果
    auto res = m*V;
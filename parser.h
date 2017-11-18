#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <armadillo>

//#include "knn_classifier.h"

using namespace std;
using namespace arma;


class Data {
protected:
	string datafile;
	vector<float> classes;
	fmat train_mat;	
	fmat test_mat;
	vector<vector<int>> combinations;
	vector<int> c; 
	vector<int> a; 

public:
	Data(string dat);
	void set_param();
	void find_feat_combo();
	void go(int offset, int k);
	fmat get_train_mat();
	fmat get_test_mat();
	void set_train_mat(fmat new_train_mat);
	void set_test_mat(fmat new_test_mat);
	vector<vector<int>> get_comb();
};		


#endif

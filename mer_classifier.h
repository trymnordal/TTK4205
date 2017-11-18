#ifndef MER_CLASSIFIER_H_
#define MER_CLASSIFIER_H_

#include <iostream>
#include <armadillo>
#include <cmath>
#include "parser.h"

using namespace std;
using namespace arma;

class MinErrRate {

	vector<fmat> train_classes;
	fmat test_mat;

	int n_obj;
	
	vector<fmat> W_i;
	vector<fvec> w_i;
	vector<float> w_i0;

public:

	MinErrRate(Data data);
	void train();
	imat classify();

};

#endif

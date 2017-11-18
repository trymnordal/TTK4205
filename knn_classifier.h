#ifndef KNN_CLASSIFIER_H_
#define KNN_CLASSIFIER_H_


#include <iostream>
#include <algorithm>
#include <armadillo>
#include "parser.h"

using namespace std;
using namespace arma;

float estimate_err(imat result);

class kNN {
private:
	int n_classes;
	fmat train_mat;
	fmat test_mat;

public:

	kNN(Data dataset);
	float classify();

};


#endif

#ifndef LS_CLASSIFIER_H_
#define LS_CLASSIFIER_H_

#include <iostream>
#include <armadillo>
#include "parser.h"

using namespace std;
using namespace arma;

class LeastSquare {
protected:	
	fmat Y;
	fmat test_mat;
	fvec a;
	fvec b;

public:

	LeastSquare (Data dataset);
	void train();
	imat classify();

};

#endif

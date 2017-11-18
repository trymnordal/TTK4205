#include "ls_classifier.h"

LeastSquare::LeastSquare(Data dataset){
	
	fcolvec mask(dataset.get_train_mat().n_rows);
	mask.ones();
	
	Y = dataset.get_train_mat();
	Y.shed_col(0);
	Y.insert_cols(0,mask);

	a.zeros(Y.n_cols-1);
	b.zeros(Y.n_rows);
	
	test_mat = dataset.get_test_mat();
	test_mat.insert_cols(1,mask);
	
	fmat temp = dataset.get_train_mat();
	
	
	int k=0;

	for (fmat::col_iterator i=temp.begin_col(0); i!=temp.end_col(0); ++i){

		if (*i==1) {
			b(k) = 1.0;
		}
	
		else {
			b(k) = -1.0;
		}
		k++;
	}

	train();
	
}

void LeastSquare::train(){
	
	a = inv(Y.t() * Y) * Y.t() * b;
}

imat LeastSquare::classify(){
	
	float g;
	
	imat result = conv_to<imat>::from(test_mat);
	result.shed_cols(1,result.n_cols-1);
	result.insert_cols(1,1);

	for(int i=0; i < test_mat.n_rows; ++i){
		
		frowvec y = test_mat.row(i);
		y.shed_col(0);
		
		fmat g = a.t()*y.t();
		
		if(g(0,0)>0){
			result(i,1) = 1;
		}
		else {
			result(i,1) = 2;
		};
	
	}
	
	return result;

}



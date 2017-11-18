#include "knn_classifier.h"

#define inf .1E+10

kNN::kNN (Data dataset){
	train_mat = dataset.get_train_mat();
	test_mat = dataset.get_test_mat();
	n_classes = 2;
}

float kNN::classify(){
	
	float min_val;
	int k;

	imat result = conv_to<imat>::from(test_mat);
	result.shed_cols(1,result.n_cols-1);
	result.insert_cols(1,1);

	for(int obj=0; obj<test_mat.n_rows; ++obj){

		k = 0;
		min_val = inf;
		frowvec x, x_i;
		
		x = test_mat.row(obj);
		x.shed_col(0);
		
		for(int i=0; i<train_mat.n_rows; ++i){
			x_i = train_mat.row(i);
			x_i.shed_col(0);
			if (norm(x-x_i)<min_val){
				min_val=norm(x-x_i);
				k = i;
			}
		
		}

		result(obj,1) = train_mat(k,0);
	}

	return estimate_err(result);

}

float estimate_err(imat result){
	
	imat C(2,2,fill::zeros);
	int i,j,err1,err2;

	for(int obj=0; obj<result.n_rows; obj++){
		
		i = result(obj,0)-1;
		j = result(obj,1)-1;

		C(i,j) += 1;
	}

	err1 = C(0,1);
	err2 = C(1,0);

	float err =(float) (err1+err2)/accu(C);

	return err;
}

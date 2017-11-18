#include "mer_classifier.h"



MinErrRate::MinErrRate(Data data) : test_mat(data.get_test_mat()) {

	int n_classes;

	fmat new_class_mat;
	fvec new_class_vec;
	float new_class_float;

	frowvec new_row;
	int i;

	for(i=0; i<data.get_train_mat().n_rows; ++i){

		if(n_classes!=data.get_train_mat()(i,0)){
			n_classes = data.get_train_mat()(i,0);
			train_classes.push_back(new_class_mat);
			W_i.push_back(new_class_mat);
			w_i.push_back(new_class_vec);
			w_i0.push_back(new_class_float);
			i--;
			continue;
		}

		new_row = data.get_train_mat().row(i);
		new_row.shed_col(0);

		train_classes[n_classes-1].insert_rows(train_classes[n_classes-1].n_rows, new_row);

	}

	n_obj = i;

	train();

}

void MinErrRate::train(){
	
	fmat current_class;
	int n_current_class = 0;

	for(vector<fmat>::const_iterator i = train_classes.begin(); i != train_classes.end(); ++i){
		
		fvec mu;
		fmat sigma;
		
		current_class = *i;

		mu = (1/(float)current_class.n_rows)*sum(current_class,0).t();

		fmat mat_sum(current_class.n_cols,current_class.n_cols,fill::zeros);
		fvec x_k;
		for(int j=0; j<current_class.n_rows; ++j){
			x_k = current_class.row(j).t();
			mat_sum += (x_k-mu)*(x_k.t()-mu.t());
		}

		sigma = (1/(float)current_class.n_rows)*mat_sum;

		float P = (float) current_class.n_rows/n_obj;

		W_i[n_current_class] = - 0.5*sigma.i();
		w_i[n_current_class] = sigma.i()*mu;
		w_i0[n_current_class] =(float) as_scalar(- 0.5*mu.t()*sigma.i()*mu) - 0.5*log((float)det(sigma)) + log(P);
	
		n_current_class++;
	}

}

imat MinErrRate::classify(){
	
	float g;
	imat result = conv_to<imat>::from(test_mat);
	result.shed_cols(1,result.n_cols-1);
	result.insert_cols(1,1);
	fvec x;

	for(int i=0; i<test_mat.n_rows; ++i){
		x = test_mat.row(i).t();
		x.shed_row(0);
		g =(float) as_scalar(x.t()*W_i[0]*x - x.t()*W_i[1]*x) + as_scalar(w_i[0].t()*x - w_i[1].t()*x) + w_i0[0] - w_i0[1];
		if(g>=0){
			result(i,1) = 1;
		}
		else result(i,1) = 2;
	}
	return result;
	

}



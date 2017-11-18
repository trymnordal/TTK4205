
#include <vector>

#include "ls_classifier.h"
#include "parser.h"
#include "knn_classifier.h"
#include "mer_classifier.h"

#define inf .1E+10


void set_optimal_feat_comb(Data &dataset, int feat_dim){
	
	float min_val = inf;
	vector<vector<int>> combs = dataset.get_comb();
	fmat temp_train, temp_test, best_train_mat, best_test_mat;

	temp_train = dataset.get_train_mat();
	temp_test = dataset.get_test_mat();

	cout<<"\n"<<"Combinations and their estimated error rate:"<<endl;

	for (int i=0; i<combs.size(); ++i){
		
		if (combs[i].size()!=feat_dim) continue;

		fmat new_train_mat = temp_train.col(0);
		fmat new_test_mat = temp_test.col(0);

		cout<<"\t";
		
		for(int j=0; j<combs[i].size(); ++j){

			new_train_mat.insert_cols(j+1, temp_train.col(combs[i][j]));
			new_test_mat.insert_cols(j+1, temp_test.col(combs[i][j]));

			cout<<combs[i][j]<<" ";

		}

	
		dataset.set_train_mat(new_train_mat);
		dataset.set_test_mat(new_test_mat);
		
		kNN classifier (dataset);
	
		cout<<"\t"<<classifier.classify()<<endl;

		if (classifier.classify()<min_val){
			min_val = classifier.classify();
			best_train_mat = new_train_mat;
			best_test_mat = new_test_mat;
		}

	}

	dataset.set_train_mat(best_train_mat);
	dataset.set_test_mat(best_test_mat);

}

int main(int argc, char* argv[]){
	
	for (int i=1; i<5; ++i){
		string file ("data/ds-3.txt"); 
		Data dataset(file);
			
		set_optimal_feat_comb(dataset, i);

		LeastSquare ls(dataset);
		MinErrRate mer(dataset);
		kNN knn(dataset);
	
		cout<<"Least square: \t"<<estimate_err(ls.classify())<<endl;
		cout<<"Min err rate: \t"<<estimate_err(mer.classify())<<endl;
		cout<<"kNN: \t\t"<<knn.classify()<<endl;
	}

	return 0;
}



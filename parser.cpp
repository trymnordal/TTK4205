
#include "parser.h"
#include "ls_classifier.h"


Data::Data(string dat) : datafile(dat) {

	set_param();
}

void Data::set_param(){
	
	string line;
	ifstream filestream;

	filestream.open(datafile.c_str());
	
	int n_obj = 0;

	if (filestream.is_open()){
		while (getline(filestream,line)){

			frowvec feature_vec(line);

			if(find(classes.begin(), classes.end(), feature_vec(0)) == classes.end()){
				classes.push_back(feature_vec(0));
			}

			if(n_obj%2==0) train_mat.insert_rows(train_mat.n_rows,feature_vec);

			else test_mat.insert_rows(test_mat.n_rows,feature_vec);

			n_obj++;
			
		}
		filestream.close();
	}

	else cout << "Unable to open file\n";
	
	find_feat_combo();

}

void Data::find_feat_combo(){
	
	int n = train_mat.n_cols-1;

	for(int i = 0; i<n; ++i){
		a.push_back(i+1);
	}

	for (int i=0; i<n; ++i){
		go(0,i+1);
	}
	
}

void Data::go(int offset, int k){
	
	if(k==0){
		combinations.push_back(c);
		return;
	}

	for (int i=offset; i<=a.size()-k; ++i){
		c.push_back(a[i]);
		go(i+1,k-1);
		c.pop_back();
	}
}

fmat Data::get_train_mat(){
	return train_mat;
}

fmat Data::get_test_mat(){
	return test_mat;
}

void Data::set_train_mat(fmat new_train_mat){
	train_mat = new_train_mat;
}

void Data::set_test_mat(fmat new_test_mat){
	test_mat = new_test_mat;
}

vector<vector<int>> Data::get_comb(){
	return combinations;
}

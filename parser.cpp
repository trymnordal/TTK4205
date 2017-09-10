#include "parser.h"

DataParser::DataParser () {
	
	string dir ("data/");
	
	while(1){
		cout << "\nDatasets you can choose:\n";	
		system("ls data");

		cout << "\nEnter dataset filename: ";
		cin >> filename;
		filename = dir+filename;
		cout << "You chose datafile: " << filename << endl;
		
		filestream.open(filename);
		if (filestream.is_open()){
			filestream.close();
			break;
		}	
		cout << "Unable to open file\n";
	}

}


string DataParser::read_line(int line_num){
	
	string line;
	int n = 0;
	filestream.open(filename);
	if (filestream.is_open()){
		while (getline(filestream,line)){
			if(line_num == n){
				break;
			}	
			n++;
		}
		filestream.close();
	}
	else cout << "Unable to open file\n";
	cout<<n<<endl;

	return line;
}

fvec DataParser::get_row_vec(){

	string temp = read_line(4);
	fvec row_vec(temp);
	row_vec.shed_row(0);
	row_vec.print();
	row_vec.save("test.txt");
	return row_vec;
}

int main(){
	
	DataParser test;
	string lol = test.read_line(4);
	test.get_row_vec();
	cout << lol << endl;
	fvec test2;
	test2.load("test.txt");
	test2.print();
	
	return 0;	
}




#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <armadillo>

using namespace std;
using namespace arma;


class DataParser {

	string filename;
	ifstream filestream;
		
public:
	DataParser();
	string read_line(int line_num);
	fvec get_row_vec();
};

int main();

#endif

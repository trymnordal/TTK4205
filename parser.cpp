#include <iostream>
#include <ifstream>


class Parser {
	int dataset;
	ifstream datafile;
	
public:
	Public(int dataset);
	void read_line();
}

Parser::Parser (int dataset) : dataset(dataset) {

	switch (dataset) {
	case 1:
		datafile ("data/ds-1.txt");
	case 2:
		datafile ("data/ds-2.txt");
	case 3:
		datafile ("data/ds-3.txt");
	}	

}

void read_line(){
	
}

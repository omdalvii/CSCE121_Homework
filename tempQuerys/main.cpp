# include "TemperatureDatabase.h"
# include <iostream>

using std::cout, std::endl;

int main(int argc, char** argv) {
	

	if (argc < 3) {
		cout << "Usage: " << argv[0] << " data_file query_file" << endl;
		return 1;
	} else {
		TemperatureDatabase database;
		database.loadData(argv[1]);
		database.outputData(argv[1]); // comment out before submitting Part 2
		database.performQuery(argv[2]); // will be done in Part 2
	}
}

void test() {
	LinkedList testList;

	testList.insert("123", 2015, 12, 79.5);
	testList.print();
	cout << endl << endl;

	testList.insert("456", 2012, 3, 95.0);
	testList.print();
	cout << endl << endl;
	
	testList.insert("456", 2009, 7, 42.8);
	testList.print();
	cout << endl << endl;
	
	testList.insert("123", 2005, 2, 69.2);
	testList.print();
	cout << endl << endl;
}

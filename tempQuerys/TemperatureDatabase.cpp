# include "TemperatureDatabase.h"
# include <fstream>
# include <sstream>

using std::cout, std::endl, std::string, std::ofstream, std::ifstream;

TemperatureDatabase::TemperatureDatabase() {}
TemperatureDatabase::~TemperatureDatabase() {}

void TemperatureDatabase::loadData(const string& filename) {
	ifstream datain(filename);

	if(!datain.is_open()) {
		cout << "Error: unable to open " << filename << endl;
		exit(1);
	}

	while (!datain.eof()) {
		string location;
		int year, month;
		double temp;

		bool valid1 = true, valid2 = true;
		string line;

		// Get line of data and check for correct amount of arguments
		getline(datain, line);
		int argCount = 1;
		for (unsigned int i = 0; i < line.length(); i++){
			if(line.at(i) == ' '){
				argCount++;
			}
		}
		if(argCount == 4){
			std::stringstream ss(line);
			ss >> location >> year >> month >> temp;
		}
		else {
			cout << "Error: Other invalid input" << endl;
			valid1 = false;
		}

		// If data acquired, check
		if (valid1) {
			//Check valid date
			if (year > 2023 || year < 1800) {
				cout << "Error: Invalid year " << year << endl;
				valid2 = false;
			}
			if (month < 1 || month > 12) {
				cout << "Error: Invalid month " << month << endl;
				valid2 = false;
			}

			//Check temp data
			if (temp < -50 || temp > 50) {
				cout << "Error: Invalid temperature " << temp << endl;
				valid2 = false;
			}

			if (valid2){
				records.insert(location, year, month, temp);
			}
		}
	}
}

void TemperatureDatabase::outputData(const string& filename) {
	ofstream dataout("sorted." + filename);
	
	if (!dataout.is_open()) {
		cout << "Error: Unable to open " << filename << endl;
		exit(1);
	}

	dataout << records.print();
}

void TemperatureDatabase::performQuery(const string& filename) {
	// TODO: implement this function
}

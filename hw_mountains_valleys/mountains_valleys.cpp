#include <iostream>
#include "functions.h"

using std::cout, std::cin, std::endl;

int main() {
	int a; 
	int b;
	
	// Get user input
	cout << "Enter numbers 10 <= a <= b < 10000: ";
	cin >> a >> b;

	// If invalid input, output error message and reprompt for input
	while(!is_valid_range(a, b)){
		cout << "Invalid Input" << endl;
		cout << "Enter numbers 10 <= a <= b < 10000: ";
		cin >> a >> b;
	}

	// Compute number of mountains/valleys and output
	count_valid_mv_numbers(a, b);
	
	return 0;
}
#include <iostream>
#include "functions.h"

using std::cout, std::endl;

bool is_valid_range(int a, int b)
{
	// Valid Range Conditions:
	// * b must be greater than a
	// * entire range must be between 10 (inclusive) and 10,000 (exclusive)
	// * 10 <= a <= b < 10000

	if (10 <= a && a <= b && b < 10000)
	{
		return true;
	}
	return false;
}

char classify_mv_range_type(int number)
{
	// Initial values for variables
	int d2 = number % 10;
	number = number / 10;
	int lastVal = 0;
	int currVal = 0;

	while (number != 0)
	{
		int d1 = number % 10; // Get next value from left

		if (d1 == d2)
		{
			break;
		} // If two digits next to eachother are equal, break out (N)

		if (lastVal != 1 && lastVal != -1)
		{
			// Set initial value for lastValue if first iteration
			lastVal = (d1 > d2) ? -1 : 1;
		}
		else
		{
			// Run for all next iterations
			currVal = (d1 > d2) ? -1 : 1; // -1 if d1 > d2, 1 if d1 < d2

			if (currVal == lastVal)
			{
				break;
			} // If same direction 2x in a row, break out (N)

			// Set currVal to lastVal for next iteration
			lastVal = currVal;
		}

		// Set d2 to d1 for next iteration
		d2 = d1;

		number = number / 10; // Take off last digit of number so loop can proceed
		if (number == 0)
		{
			// If last iteration and everything has been alternating, can use
			// the last value computed to determine if valley/mountain
			if (lastVal == -1)
			{
				return 'V';
			}
			else if (lastVal == 1)
			{
				return 'M';
			}
		}
	}

	// If nothing returned inside while loop, that means no mountains/valleys
	// so return N
	return 'N';
}

void count_valid_mv_numbers(int a, int b)
{
	int mountainRanges = 0;
	int valleyRanges = 0;
	int i;

	for (i = a; i <= b; ++i)
	{
		// Go through each int between a and b (inclusive) and check if mountain/valley,
		// then if so add a count to its respective variable
		char type = classify_mv_range_type(i);

		mountainRanges += (type == 'M') ? 1 : 0;
		valleyRanges += (type == 'V') ? 1 : 0;
	}

	// Use counts to output final message
	cout << "There are " << mountainRanges << " mountain ranges and " << valleyRanges << " valley ranges between " << a << " and " << b << "." << endl;
}
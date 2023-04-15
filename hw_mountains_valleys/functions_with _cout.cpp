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
	// DEBUG PRINT STATEMENT
	cout << "Original number: " << number << endl;
	cout << endl;

	// Initial values for variables
	int rightDigit = number % 10; // Get rightmost digit
	number = number / 10;		  // Delete rightmost digit from number
	int previousDirection = 0;	  // Initial values for previous
	int currentDirection = 0;	  // and current direction

	while (number != 0)
	{
		// Get new values
		int leftDigit = number % 10; // Get new rightmost digit in number (number to the left of rightDigit)

		// DEBUG PRINT STATEMENT
		cout << "Left number: " << leftDigit << ", Right Number:" << rightDigit << endl;

		// Check direction
		if (leftDigit > rightDigit)
		{
			// DEBUG PRINT STATEMENT
			cout << "going down" << endl;

			currentDirection = -1; // Set currentDirection to -1, representing decreasing
		}
		else if (leftDigit < rightDigit)
		{
			// DEBUG PRINT STATEMENT
			cout << "going up" << endl;

			currentDirection = 1; // Set currentDirection to 1, representing increasing
		}
		else if (leftDigit == rightDigit)
		{
			// DEBUG PRINT STATEMENT
			cout << "equal, not a valid range" << endl;

			break; // Break out of while loop since we know this isn't a valid range (N)
		}

		// Check if direction is alternating
		if (previousDirection == 0)
		{
			// For first iteration, gets the 'previousDirection' variable initialized with a value
			previousDirection = currentDirection;
		}
		else if (previousDirection != 0 && currentDirection == -previousDirection)
		{
			// DEBUG PRINT STATEMENT
			cout << "flipped direction" << endl;
		}
		else
		{
			// DEBUG PRINT STATEMENT
			cout << "same direction twice" << endl;
			break;
		}
		
		// DEBUG PRINT STATEMENT
		cout << endl;

		// Update values before next iteration of loop starts
		rightDigit = leftDigit;				  // Set rightDigit to current value of leftDigit before next iteration
		previousDirection = currentDirection; // Set previousDirection to current value of currentDirection before next iteration
		number = number / 10;				  // Take off last digit of number so loop can proceed

		// If on last iteration and haven't broken out of loop yet, that means it is a valid range
		// so we can check what the value of currentDirection is (direction between first two digits)
		// in the original number
		if (number == 0)
		{
			// DEBUG PRINT STATEMENT
			cout << "All pairs of numbers have been alternating increasing/decreasing" << endl;

			if (currentDirection == 1)
			{
				// DEBUG PRINT STATEMENT
				cout << "Starts off going up, so mountain range." << endl;
				cout << endl;

				return 'M';
			}
			else if (currentDirection == -1)
			{
				// DEBUG PRINT STATEMENT
				cout << "Starts off going down, so valley range." << endl;
				cout << endl;

				return 'V';
			}
		}
	}

	// If nothing returned inside while loop, that means no mountains/valleys
	// so return N
	cout << "N" << endl;
	cout << endl;
	return 'N';
}

void count_valid_mv_numbers(int a, int b)
{
	int mountainRangesCount = 0;
	int valleyRangesCount = 0;
	int i;

	for (i = a; i <= b; ++i)
	{
		// Go through each int between a and b (inclusive) and check if mountain/valley,
		// then if so add a count to its respective variable
		char type = classify_mv_range_type(i);

		if (type == 'M')
		{
			mountainRangesCount += 1;
		}
		else if (type == 'V')
		{
			valleyRangesCount += 1;
		}
	}

	// Use counts to output final message
	cout << "There are " << mountainRangesCount << " mountain ranges and " << valleyRangesCount << " valley ranges between " << a << " and " << b << "." << endl;
}
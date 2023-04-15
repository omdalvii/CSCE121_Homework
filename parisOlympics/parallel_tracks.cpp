#include <iostream>
#include <iomanip>
#include <string>
#include "parallel_tracks.h"

using std::string;

using std::cin;

//-------------------------------------------------------
// Name: get_runner_data
// PreCondition:  the prepped parallel arrays
// PostCondition: all arrays contain data gotten from standard in
//---------------------------------------------------------
bool get_runner_data(double timeArray[], std::string countryArray[],
					 unsigned int numberArray[], std::string lastnameArray[])
{
	// Temp values for performing data validation
	double time;
	unsigned int number;
	string country, lastname;

	// Get data and validate data
	for (unsigned int i = 0; i < SIZE; i++)
	{
		// Get values from input
		cin >> time;
		cin >> country;
		cin >> number;
		cin >> lastname;
		lastname = trim(lastname);

		// Check that data is valid
		// TIME
		if (time <= 0) // Time must be a positive, non-zero number
		{
			return false;
		}

		// COUNTRY
		if ((int)country.length() != 3) // Country code must be 3 letters
		{
			return false;
		}
		else
		{
			for (int j = 0; j < 3; j++) // Check each character
			{
				// Country code must be all capital letters
				// 'A' = 65, 'Z' = 90
				// value of characters must be between 65 & 90, inclusive
				if (!(country[j] >= 65 && country[j] <= 90))
				{
					return false;
				}
			}
		}

		// NUMBER
		if (number / 100 > 0) // Number must be 1 or 2 digits
		{
			return false;
		}

		// LASTNAME
		if ((int)lastname.length() <= 1) // Last name must be more than one character
		{
			return false;
		}
		else
		{
			for (int j = 0; j < (int)lastname.length(); j++)
			{
				// Last name must be all letters
				// 'A' = 65, 'Z' = 90
				// 'a' = 97, 'z' = 122
				// value of characters must be between 65 & 90 (inclusive) OR 97 & 122 (inclusive)

				if (!((lastname[j] >= 65 && lastname[j] <= 90) || (lastname[j] >= 97 && lastname[j] <= 122)))
				{
					return false;
				}
			}
		}

		// If all data is valid, add to arrays and move on to next set
		timeArray[i] = time;
		countryArray[i] = country;
		numberArray[i] = number;
		lastnameArray[i] = lastname;
	}

	return true; // If none of the data validation checks return a false, then true will be returned
}

//-------------------------------------------------------
// Name: prep_double_array
// PreCondition:  an array of doubles is passed in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_double_array(double ary[])
{
	// making sure all values within the array are set to 0.0;
	for (unsigned int i = 0; i < SIZE; i++)
	{
		ary[i] = 0.0;
	}
}

//-------------------------------------------------------
// Name: prep_unsigned_int_array
// PreCondition:  an array of unsigned ints is passed in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_unsigned_int_array(unsigned int ary[])
{
	// making sure all values within the array are set to 0;
	for (unsigned int i = 0; i < SIZE; i++)
	{
		ary[i] = 0;
	}
}

//-------------------------------------------------------
// Name: prep_string_array
// PreCondition:  an array of strings is passed in
// PostCondition: each element in the array is set to "N/A"
//---------------------------------------------------------
void prep_string_array(std::string ary[])
{
	// making sure all values within the array are set to "N/A";
	for (unsigned int i = 0; i < SIZE; i++)
	{
		ary[i] = "N/A";
	}
}

//-------------------------------------------------------
// Name: get_ranking
// PreCondition:  just the time array is passed in, and has valid data
// PostCondition: after a very inefficient nested loop to determine the placements
// and places the ranks in a new array. That new array is returned
//---------------------------------------------------------
void get_ranking(const double timeArray[], unsigned int rankArray[])
{
	double highestTime = timeArray[0];
	for(unsigned int i = 0; i < SIZE; i++){
		highestTime = (timeArray[i] > highestTime) ? timeArray[i] : highestTime;
	}


	for (unsigned int i = 0; i < SIZE; i++)
	{
		double lowestTime = highestTime;
		unsigned int rankPosition;
		for (unsigned int j = 0; j < SIZE; j++)
		{
			bool lowerTime = (timeArray[j] <= lowestTime);
			bool unusedValue = (rankArray[j] == 0);

			if ( lowerTime && unusedValue){
				lowestTime = timeArray[j];
				rankPosition = j;
			}
		}

		rankArray[rankPosition] = i+1;
	}
}

//-------------------------------------------------------
// Name: print_results
// PreCondition:  all parallel arrays are passed in and have valid data
// PostCondition: after a very inefficient nested loop to determine the ranks
// it then displays them along with a delta in time from the start
//---------------------------------------------------------
void print_results(const double timeArray[], const std::string countryArray[],
				   const std::string lastnameArray[], const unsigned int rankArray[])
{

	std::cout << "Final results!!";
	std::cout << std::setprecision(2) << std::showpoint << std::fixed << std::endl;
	double best_time = 0.0;

	// print the results, based on rank, but measure the time difference_type
	for (unsigned int j = 1; j <= SIZE; j++)
	{

		// go thru each array, find who places in "i" spot
		for (unsigned int i = 0; i < SIZE; i++)
		{
			if (rankArray[i] == 1) // has to be a better way, but need the starting time
			{
				best_time = timeArray[i];
			}

			if (rankArray[i] == j) // then display this person's data
			{
				// this needs precision display
				std::cout << "[" << j << "]  " << timeArray[i] << " " << std::setw(15) << std::left << lastnameArray[i] << "\t"
						  << "(" << countryArray[i] << ")  +" << (timeArray[i] - best_time) << std::endl;
			}
		}
	}
}

std::string trim(std::string ret)
{
	// remove whitespace from the beginning
	while (!ret.empty() && isspace(ret.at(0)))
	{
		ret.erase(0, 1);
	}

	// remove whitespace from the end
	//  Note: last index is (.size() - 1) due to 0 based indexing
	while (!ret.empty() && isspace(ret.at(ret.size() - 1)))
	{
		ret.erase(ret.size() - 1, 1);
	}

	return ret;
}
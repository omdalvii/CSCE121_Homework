#include <iostream>
#include <string>
#include <stdexcept>
#include "./string_calculator.h"

using std::cout, std::endl;
using std::string;

unsigned int digit_to_decimal(char digit)
{
    if (48 <= digit && digit <= 57)
    {
        return static_cast<unsigned int>(digit) - 48;
    }
    else
    {
        throw std::invalid_argument("Not a valid digit");
    }
}

char decimal_to_digit(unsigned int decimal)
{
    if (decimal <= 9)
    {
        return static_cast<char>(decimal + 48);
    }
    else
    {
        throw std::invalid_argument("Input must be between 0-9.");
    }
}

string trim_leading_zeros(string num)
{
    bool isNegative = false;
    if (num[0] == '-')
    {
        isNegative = true;
        num = num.substr(1, num.length() - 1);
    }

    string newNum = "";
    int len = num.length();
    if (len == 0)
    {
        return "0";
    }

    int i = 0;
    while (num.at(i) == '0')
    {
        i++;
        // cout << "digit #" << i << " = 0" << endl;

        if (i == len)
        {
            return "0";
        }
    }

    for (int j = i; j < len; j++)
    {
        // cout << "new digit #" << j-i+1 << ": " << num.at(j) << endl;
        newNum += num.at(j);
    }

    if (isNegative)
    {
        newNum = '-' + newNum;
    }

    return newNum;
}

string add(string lhs, string rhs)
{
    // make strings the same length
    int len;
    int lh_len = lhs.length();
    int rh_len = rhs.length();
    if (lh_len > rh_len)
    {
        int diff = lh_len - rh_len;
        string add = "";

        for (int i = 0; i < diff; i++)
        {
            add += "0";
        }
        rhs = add + rhs;
        len = rhs.length();
    }
    else if (lh_len < rh_len)
    {
        int diff = rh_len - lh_len;
        string add = "";

        for (int i = 0; i < diff; i++)
        {
            add += "0";
        }
        lhs = add + lhs;
        len = lhs.length();
    }
    else
    {
        len = lhs.length();
    }

    // addition operation
    int carry = 0;
    string result = "";
    for (int i = len - 1; i >= 0; i--)
    {
        unsigned int n1, n2, sum;
        n1 = digit_to_decimal(lhs[i]);
        n2 = digit_to_decimal(rhs[i]);

        sum = carry + n1 + n2;

        result = decimal_to_digit(sum % 10) + result;
        carry = sum / 10;
    }

    if (carry != 0)
    {
        result = decimal_to_digit(carry) + result;
    }

    // cout << lhs << "  " << rhs << endl;
    return trim_leading_zeros(result);
}

string multiply(string lhs, string rhs)
{
    // lhs * rhs --> lhs + lhs + ... + lhs (added to itself rhs-1 times)
    // for each digit higher, can do same and multiply by 10 (eg; lhs * 20 = lhs * 2 * 10)

    lhs = trim_leading_zeros(lhs);
    rhs = trim_leading_zeros(rhs);
    int lh_len = lhs.length();
    int rh_len = rhs.length();

    // Negatives logic
    bool isNegative = false;
    if (lhs[0] == '-' && rhs[0] == '-')
    {
        lhs = lhs.substr(1, lh_len - 1);
        rhs = rhs.substr(1, rh_len - 1);
    }
    else if (lhs[0] == '-' && rhs[0] != '-')
    {
        lhs = lhs.substr(1, lh_len - 1);
        isNegative = true;
    }
    else if (rhs[0] == '-' && lhs[0] != '-')
    {
        rhs = rhs.substr(1, rh_len - 1);
        isNegative = true;
    }

    string finalSum = "0";
    int iterCount = 0;
    for (int i = rh_len - 1; i >= 0; i--)
    { // i = index of current digit in rhs we are looking at
        string sum_temp = lhs;
        string addZeros = "";

        // cout << rhs[i] << " * " << lhs << endl;

        for (unsigned int j = 1; j < digit_to_decimal(rhs[i]); j++)
        { // "multiplies" lhs by rhs[i]
            sum_temp = add(sum_temp, lhs);
        }
        for (int k = 0; k < iterCount; k++)
        { // "multiplies" result by appropiate number of 10's to make it the correct plave
            addZeros += "0";
        }
        sum_temp = sum_temp + addZeros;

        // cout << i << " place: sum -> " << sum_temp << endl;

        if (rhs[i] != '0')
        {
            finalSum = add(finalSum, sum_temp);
        } // adds result to final sum
        iterCount++;
    }

    if (isNegative)
    {
        finalSum = '-' + finalSum;
    }

    return finalSum;
}

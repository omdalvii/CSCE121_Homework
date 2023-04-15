#include <iostream>
#include <string>
#include <limits>
#include "./string_calculator.h"

using std::cout, std::endl, std::cin;
using std::string;

int main() {
    cout << "String Calculator" << endl;
    cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl;
    cout << ">>" << endl;
    
    // Initialize variables
    string input;
    char operation = '\0';

    // Prompt initial input
    getline(cin, input);

    // Loop while input is not asking to quit
    while (input != "q" && input != "quit"){
        // Figure out which operation is being requested
        if(input.find('+') != string::npos){
            operation = '+';
        }else if(input.find('*') != string::npos){
            operation = '*';
        }

        int operatorLoc = input.find(operation);
        string lhs, rhs, result;

        lhs = input.substr(0, operatorLoc-1);
        rhs = input.substr(operatorLoc+2, input.length());

        try{
        switch(operation){
            case '+':
                result = add(lhs, rhs);
                break;

            case '*':
                result = multiply(lhs, rhs);
                break;

            default:
                result = "operation not defined";
                break;
        }
        
        
        cout << "ans =" << endl << endl
             << "    " << result << endl 
             << endl;

        }
        catch(std::invalid_argument& excpt){
            cout << "Invalid Argument Error: " << excpt.what() << endl;
        }

        //prompt next input and reset necessary variables
        operation = '\0';
        cout << ">>" << endl;
        getline(cin, input);
    }

    // Goodbye message
    cout << "farvel!" << endl;
}


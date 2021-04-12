#pragma once
//header guard
#include <iostream>
#ifndef AIRGEAD
#define AIRGEAD
/*Include InvestmentProfile Header, as this class declaration creates a pointer to 
an InvestmentProfile object it will use for its lifespan*/
#include "InvestmentProfile.h"; 

using namespace std;

//this class acts as an "instance" of the application- it should not be destroyed, as it will exist as long as the program is running
class Airgead {
//public members of Airgead class
public:
	Airgead(); //constructor. This constructor takes no arguments, but does create an instance of InvestmentProfile for its own use.

	/*This function asks the user for the necessary data and modifies the 
	* instance of InvestmentProfile for use */
	void modifyInvestmentProfile(); 

	/*This function will print the investment report's results
	* its argument, t_mthly, determines whether the report is printed:
	* with mothly deposits (if t_mthly is true), or
	* without monthly deposits (if t_mthly is false)*/
	void printReport(bool t_mthly);

//private members of Airgead class
private:
	//ClearScreen function, used to clear screen for clear display of data
	void clearScreen();

	/*Function template. As both floats and ints are required by InvestmentProfile,
	* this function can be called to return either data type.
	* It accepts one argument, t_expectedInput, which represents what sort of input it expects.
	* This value should be a string of either:
	* "dollars" - helps ensure that the user's input is a money amount, and converts it into a float of precision 2
	* "interest" - helps ensure the user's input is an interest rate, and converts it into a float of precision 3
	* "years" - helps ensure the user's input is a whole number of years, converted to an integer and stored*/
	template <typename DataType> DataType parseInput(const string& t_ExpectedInput);

	/*creates an automatically managed pointer to its instance of InvestmentProfile. Only one instance will ever be made,
	* and that will be done upon creation of an instance of Airgead*/
	unique_ptr<InvestmentProfile> invProfile;
	
};
#endif AIRGEAD
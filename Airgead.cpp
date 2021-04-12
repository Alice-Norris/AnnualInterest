#include "Airgead.h";
#include <regex>;
#include <iomanip>;


Airgead::Airgead(){ //Airgead's constructor. This constructor takes no arguments, but does create an instance of InvestmentProfile for its own use.
	//creates new instance of InvestmentProfile using its default constructor, and a pointer to it
	invProfile = unique_ptr<InvestmentProfile>(new InvestmentProfile()); 
}

//simple function to clear screen of terminal
void Airgead::clearScreen() {
	for (int i = 0; i < 40; ++i) { // sets i to 0, increments i until i = 40
		cout << endl; //print an endline, scrolling the terminal by 1
	}
}

//function template, used to return different data types depending upon the argument t_expectedInput
template<typename DataType>DataType Airgead::parseInput(const string& t_ExpectedInput) {
	string stringToConvert; //string that will be converted after it is input by the user
	
	/* create an instance of smatch, a class template of match_results, which holds 
	* matches discovered by a regex function (in this case, regex_search)*/
	smatch matches; 
	/*create regex, but make it empty, to be changed later. Can be used by a regex function,
	here, regex_search, to find substrings that match it.*/
	regex inputValidator("");
	/* The do loop below has a while condition of: matches[0].length=0; 
	This was used because the regexes defined here will match on an empty or invalid string, but the first match will be
	a string of length 0. So long as the user provides input that does not match, this will execute*/
	do { 
		/*try loop to ensure that no attempt is made to convert an empty or otherwise invalid string to 
		* a float or integer. If this occurs, an "invalid_argument" exception will be thrown.*/
		try { 
			cin >> stringToConvert; //take input from user to be converted
			if (t_ExpectedInput == "dollars") { //argument "dollars" passed to function, modify regex accordingly
				/*This sets the inputValidator regex such that
				 it will match on a string of the following formats:
				 "*.**", "*.*", ".*", "*", or even "*.",
				 either preceded or followed by a dollar sign.
				 The matched string will have up to two decimal places,
				 and will discard the dollar sign symbol.
				 Note that the parentheses puts the string we're interested in
				 in its own matching group in smatches, accessed from smatches as the second item in its
				 array of matches*/
				inputValidator = regex("\\$?(\\d*\\.?\\d{0,2})\\$?"); 
			}
			else if (t_ExpectedInput == "interest") { //argument "interest passed to function, modify regex accordingly
				/*This sets the inputValidator regex such that
				 it will match on a string of the following formats:
				 "*.**", "*.*", ".*", "*", or even "*.",
				 either preceded or followed by a percentage sign.
				 The matched string will have up to three decimal places,
				 and will discard the percentage symbol.
				 Note that the parentheses puts the string we're interested in 
				 in its own matching group in smatches, accessed from smatches as the second item in its
				 array of matches*/
				inputValidator = regex("\\%?(\\d*\\.?\\d{0,3})\\%?");
			}
			else if (t_ExpectedInput == "years") { //argument "years" passed to function, modify regex accordingly
				/*This sets the inputValidator regex such that
				it will match only on a whole integer. 
				It will match on any string of numbers, including decimals,
				but only the whole integer number will be converted, discarding and NOT rounding*/
				inputValidator = regex("\\d+");
			}
			else {
				cout << "Invalid Function Call!"; //if somehow the function gets called with any other string, do nothing
			}
			/*regex_search takes the following arguments:
			* stringToConvert: the string provided by the user to be converted
			* matches: passes the smatches instance created earlier, used to store relevant substrings
			* inputValidator: the regex created earlier, used to find relevant substrings*/
			regex_search(stringToConvert, matches, inputValidator);
			/* Ensures that the first matche found has a length greater than zero,
			* and that either a dollar amount or interest rate is expected. Both are stored as floats.
			* the first entry in smatch's array will be the entire string it matched on, 
			* where as the second entries and further will be substrings that match parentheses in the regex*/
			if (matches[0].length() > 0 && (t_ExpectedInput == "dollars" || t_ExpectedInput == "interest")) {
				/*convert the second match stored in matches to a float, and return it. 
				The first entry is all of user's input. the second entry is the relevant substring. */
				return stof(matches[1]); 
			}
			/* Ensures that the first match found has a length greater than zero,
			* and that an integer representing number of years is expected.
			* as this regex has no parentheses, the first match will be the relevant one, and is looking only
			* for a whgole number.*/
			else if (matches[0].length() > 0 && t_ExpectedInput == "years") {
				return stoi(matches[0]); //converts the first match in matches to an integer and returns it
			}
			else {
				/*if the first match in any case has a zero-length, any further matches will be invalid for passing to stof() or stoi()
				* the input received is invalid and can not be used. Therefore, the same exception that stof or stoi would throw is thrown*/
				throw invalid_argument("No matches!"); 
			}

		}
		catch (const invalid_argument& error) { //despite guarding against it getting this far, should stof or stoi receive invalid input, handle it
			cerr << "No valid input detected!" << endl; //let user know that their input was invalid
			//inlined functions designed to tell user specifically what went wrong
			if (t_ExpectedInput == "dollars") { cerr << "Please enter a dollar amount in decimal format!" << endl; }
			else if (t_ExpectedInput == "interest") { cerr << "Please enter an interest rate in decimal format!" << endl; }
			else if (t_ExpectedInput == "years") { cerr << "Please enter a number of years as a whole number!" << endl; }
		}
	} while (matches[0].length() == 0); //as explained above, repeats the loop until valid input is received, which will always have a length longer than zero
}

/*This function is used to ask the user for relevant information,
* showing the InvestmentProfile instance's previous values if applicable, 
* then calls the relevant function from InvestmentProfile, and calls ParseInput,
* which will receive and return input in a format usable by invProfile, 
* Airgead's instance of InvestmentProfile*/
void Airgead::modifyInvestmentProfile() {
	/*check if invProfile, Airgead's instance of InvestmentProfile, has the default value for initial investment amount. If so,
	* it has not been changed, so there is nothing to display.*/
	if (invProfile->getInitialInvestAmt() == -1) {
		cout << "Initial Investment Amount: "; //prompt user for first-run investment amount
	} else { //if invProfile's investment amount is not -1, prompt user for a new investment amount, showing the old one for convenience.
		cout << "Initial Investment Amount (Previous Amount: $" << invProfile->getInitialInvestAmt() << "): ";
	}
	/*silently calls invProfile's function to set its initial investment amount. 
	* It does this by calling ParseInput, which will gather input from the user and return a float,
	* as ParseInput is called here with a return type of float*/ 
	invProfile->setInitialInvestAmt(parseInput<float>("dollars"));

	/*check if invProfile, Airgead's instance of InvestmentProfile, has the default value for monthly deposit amount. If so,
	* it has not been changed, so there is nothing to display.*/
	if (invProfile->getMthlyDep() == -1) {
		cout << "Monthly Deposit: ";
	}
	else {//if invProfile's monthly deposit is not -1, prompt user for a new monthly deposit, showing the old one for convenience.
		cout << "Monthly Deposit (Previous Amount: $" << invProfile->getMthlyDep() << "): ";
	}
	/*silently calls invProfile's function to set its monthly deposit amount.
	* It does this by calling ParseInput, which will gather input from the user and return a float,
	* as ParseInput is called here with a return type of float*/
	invProfile->setMthlyDep(parseInput<float>("dollars"));

	/*check if invProfile, Airgead's instance of InvestmentProfile, has the default value for its interest rate. If so,
	* it has not been changed, so there is nothing to display.*/
	if (invProfile->getInterestRate() == -1) {
		cout << "Annual Interest Percentage: ";
	}
	else {//if invProfile's interest rate is not -1, prompt user for a new interest rate, showing the old one for convenience.
		cout << "Annual Interest Percentage (Previous Amount: " << invProfile->getInterestRate() << "%): ";
	}
	/*silently calls invProfile's function to set its interest rate.
	* It does this by calling ParseInput, which will gather input from the user and return a float,
	* as ParseInput is called here with a return type of float*/
	invProfile->setInterestRate(parseInput<float>("interest"));

	/*check if invProfile, Airgead's instance of InvestmentProfile, has the default value for its number of years. If so,
	* it has not been changed, so there is nothing to display.*/
	if (invProfile->getYrs() == -1) {
		cout << "Number of Years: ";
	}
	else {//if invProfile's number of years is not -1, prompt user for a new number of years, showing the old one for convenience.
		cout << "Number of Years (Previous Amount: " << invProfile->getYrs() << " years): ";
	}
	/*silently calls invProfile's function to set the number of years to calculate.
	* It does this by calling ParseInput, which will gather input from the user and return an int,
	* as ParseInput is called here with a return type of float*/
	invProfile->setYrs(parseInput<int>("years"));
	
	cout << "Press Enter to continue..." << endl; //pause program here, no surprises for user!
	cin.get(); //user doesn't have to press zero, but any input will be discarded, including the newline from the enter key
	clearScreen(); //clear screen to tidy up!
}

/*This function will handle the printing of both reports. Which report is printed depends on its only argument,
* t_mthly, which will determine which one to print. if t_mthly is false, print without accounting for monthly deposits
* if true, print the report accounting for monthly deposits*/
void Airgead::printReport(bool t_mthly) {
	clearScreen(); //clear screen to tidy up!
	//the following values are used only to keep track of key information for the report, and are discarded after the function exits.
	int currMonth = 0; //currMonth starts at zero, keeps track of how far into report we are
	float closingAmt = 0; //closing amount initialized to zero
	float annualInterest = 0; //keeps track of annual interest. 
	//the following values are taken from this instance's InvestmentProfile instance.
	int totalMonths = invProfile->getYrs() * 12; //converts invProfile's years to months, used to know when we're done
	float openingAmt = invProfile->getInitialInvestAmt(); //get invProfile's initial investment amount
	float mthlyDep = invProfile->getMthlyDep(); //get invProfile's monthly deposit amount
	float interestRate = invProfile->getInterestRate(); //get invProfile's interest rate
	if (t_mthly == false) { //if printing the report without monthly deposit, print this title to let the user know
		cout << "Balance and Interest Without Additional Monthly Deposits" << endl;
	}
	else { //if printing the report WITH monthly deposits, print this title to let the user know
		cout << "Balance and Interest With Additional Monthly Deposits" << endl;
	}
	//print report header
	cout << "========================================================================" << endl;
	/*the following line uses flags to format the way data is printed to make sure it's neat.
	* "left" changes the justification of the string to left, and "right" to the right.*/
	cout << left << "Year" << right << "\t\tYear End Balance" << right << "\t\tYear End Earned Interest" << endl; 
	cout << "------------------------------------------------------------------------" << endl;
	
	while (currMonth < totalMonths) { //while our currMonth is not at the end of the desired investment period
		//reset the total (opening amount plus deposit)
		float total = 0;
		//reset monthly interest
		float interest = 0;
		if (t_mthly == false) { //if the report without monthly deposit is being printed, do not take monthly deposits into account
			total = openingAmt;
		}
		else {
			total = openingAmt + mthlyDep; //make sure the current total includes monthly deposits if printing the report with monthly deposit
		}
		interest = total * ((interestRate / 100) / 12); //either with or without monthly deposits, calculate interest per month
		annualInterest += interest; //add this months interest to annual interest
		closingAmt = total + interest; //keep closing amount in mind, used if the currMonth comes at the end of the year
		openingAmt = closingAmt; //set opening amount to the same as closing amount, to keep track of the investment's value
		/*Since months are counted from zero, the currMonth 11 will be the twelfth month, so add 1. If that's divisible by
		* 12, we're at the end of a year, and a line needs to be printed for the report*/
		if ((currMonth + 1) % 12 == 0) { 
			//set all printed numbers to be of fixed length, precision two. left justify the year value given by dividing currMonth + 1 by twelve.
			cout << fixed << setprecision(2) << left << (currMonth + 1) / 12; 
			//right justify the whitespace and dollar sign, left align closing amount up against the dollar sign, set to field width of 20 to align columns
			cout << right << "\t\t$" << left << setw(20) << closingAmt;
			//right justify whitespace and dollar sign, left align interest up against the dollar sign, followed by an endline
			cout << right << "\t\t$" << annualInterest << endl;
			annualInterest = 0; //end of the year, reset annual Interest!
		}
		currMonth++; //increment month
	}
	cout << "Press Enter to Continue..." << endl; //pause program here
	cin.get(); //user doesn't have to press zero, but any input will be discarded, including the newline from the enter key
}
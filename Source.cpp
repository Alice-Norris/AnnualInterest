#include <iostream> //included for standard i/o
#include "Airgead.h"; //include application class
#include "InvestmentProfile.h"; //include InvestmentProfile class
using namespace std;

int main() {
	string userInput = "Y"; //Sets exit condition so that the loop will continue
	auto AppInstance = unique_ptr<Airgead>(new Airgead()); //create automatically managed instance of Airgead class and a pointer to it.
	do {
		//call Airgead instance's ModifyInvestmentProfile, used to take user input and change investment values
		AppInstance->modifyInvestmentProfile(); 
		AppInstance->printReport(false); //calls Airgead instance's PrintReport without monthly deposits
		AppInstance->printReport(true); //calls Airgead instance's PrintReport, with monthly deposits
		
		do { //while condition: if user input is not "Y" or "N", repeat until explicit answer is given
			cout << "Would you like to try again with different values? (Y/N)"; //prompt user to either exit or modify values and try again
			cin >> userInput; //take user input
			if (userInput != "N" && userInput != "Y") { //if answer is not one of the two choices, notify user
				cout << "please enter either \'Y\' to try again, or \'N\' to exit program!";
			}
		} while (userInput != "Y" && userInput != "N"); //repeat until user gives valid answer
	} while (userInput != "N"); //if user does not indicate exit,  start over
	AppInstance.reset(); //delete App instance, and with it, its instance of InvestmentProfile
}
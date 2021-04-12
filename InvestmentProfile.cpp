#include "InvestmentProfile.h"; //include Investment Profile Header

using namespace std;

//this function takes one argument, a float, t_investAmtInput, and sets m_initialInvestAmt to t_investAmtInput
void InvestmentProfile::setInitialInvestAmt(float t_investAmtInput) {
	this->m_initialInvestAmt = t_investAmtInput; //set instance's initial investment amount to the argument passed to the function
}

//this function takes no arguments, and only returns instance's m_InitialInvestAmt
float InvestmentProfile::getInitialInvestAmt() {
	return this->m_initialInvestAmt; //returns instance's intial investment amount
}

//this function takes one argument, a float, t)mthlyDepInput, and sets m_mthlyDeposit to t_mthlyDepInput
void InvestmentProfile::setMthlyDep(float t_mthlyDepInput) {
	this->m_mthlyDeposit = t_mthlyDepInput; //sets instance's monthly deposit amount to the argument passed to the function
}

//this function takes no arguments, and only returns instance's m_mthlyDeposit
float InvestmentProfile::getMthlyDep() {
	return this->m_mthlyDeposit; //returns instance's monthly deposit amount
}

//this function takes one argument, a float, tt_interestRateInput, and sets m_interestRate to t_interestRateInput
void InvestmentProfile::setInterestRate(float t_interestRateInput) {
	this->m_interestRate = t_interestRateInput; //sets instance's interest rate to the argument passed to the function
}

///this function takes no arguments, and only returns instance's m_interestRate
float InvestmentProfile::getInterestRate() { 
	return this->m_interestRate; //returns instance's interest rate as a float, in percentage form
}
//this function takes one argument, an int, t_yrsInput, and sets m_yrs to t_yrsInput
void InvestmentProfile::setYrs(int t_yrsInput) {
	this->m_yrs = t_yrsInput; //sets instance's number of years to the argument passed to the function
}

//this function takes no arguments, and only returns instance's m_yrs
int InvestmentProfile::getYrs() { 
	return this->m_yrs; //returns instance's number of years as an int
}

//Default constructor. Sets all variables to -1, to indicate that no values have been changed.
InvestmentProfile::InvestmentProfile() {
	this->m_initialInvestAmt = -1;
	this->m_mthlyDeposit = -1;
	this->m_interestRate = -1;
	this->m_yrs = -1;
}

/*This constructor, although never called, is created for the sake of completeness.
* Takes four arguments:
* t_initialInvestment: represents initial investment amount
* t_mthlyDeposit: represents monthly deposit amount
* t_interestRate: represents interest rate for investment
* t_years: represents number of years investment will be held*/
InvestmentProfile::InvestmentProfile(float t_initialInvestAmt, float t_mthlyDeposit, float t_interestRate, int t_yrs) {
	this->m_initialInvestAmt = t_initialInvestAmt;
	this->m_mthlyDeposit = t_mthlyDeposit;
	this->m_interestRate = t_interestRate;
	this->m_yrs = t_yrs;
}


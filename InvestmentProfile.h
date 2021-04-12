#pragma once
//header guard
#ifndef INVESTMENT_PROFILE_H
#define INVESTMENT_PROFILE_H
/*This class is used to keep track of the user's investment data.
* Will never be created directly, is automatically created once per creation of Airgead instance.
* It is destroyed with its Airgead instance.*/
class InvestmentProfile
{
//public members of InvestmentProfile
public:
	/*This constructor, although never called, is created for the sake of completeness.
	* Takes four arguments:
	* t_initialInvestment: represents initial investment amount
	* t_mthlyDeposit: represents monthly deposit amount
	* t_interestRate: represents interest rate for investment
	* t_years: represents number of years investment will be held*/
	InvestmentProfile(float t_initialInvestAmt, float t_mthlyDeposit, float t_interestRate, int t_yrs);
	
	//default constructor
	InvestmentProfile();

	void setInitialInvestAmt(float t_investAmtInput); //sets Initial Investment Amount, sets m_investAmt to t_investAmtInput
	float getInitialInvestAmt(); //returns Initial investment amount as a float

	void setMthlyDep(float t_mthlyDepInput); //Sets monthly deposit amount, sets m_mthlyDepInput to t_mthlyDeposit
	float getMthlyDep(); //returns monthly deposit amount as a float

	void setInterestRate(float t_interestRateInput); //Sets interest rate, sets m_interestRate to t_interestRateInput
	float getInterestRate(); //returns interest rate as a float
	 
	void setYrs(int t_yrsInput); //Sets number of years investment will be held, sets m_yrs to t_yrsInput
	int getYrs(); //returns years to be held as an int

private:
	float m_initialInvestAmt; //represents initial investment amount
	float m_mthlyDeposit; //represents monthly deposit amount
	float m_interestRate; //represents interest rate as a percentage
	int m_yrs; //represents years for investment to be held
};

#endif //INVESTMENT_PROFILE_H

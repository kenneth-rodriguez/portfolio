#pragma once

#ifndef AIRGEADBANKING_Calculator_H
#define AIRGEADBANKING_Calculator_H

//Declare functions and variables used for calculating and printing interest
class Calculator
{
public:
	//Draw results of interest calculations without monthly deposits
	//(Takes the initial investment, the annual interest rate, and the number of years)
	void interestWithoutMonthly(double t_initInvestment, double t_annualInterest, int t_numOfYears);

	//Draw results of interest calculations with monthly deposits
	//(Takes the initial investment, monthly deposit amount, the annual interest rate, and the number of years)
	void interestWithMonthly(double t_initInvestment, double t_monthlyDeposit, double t_annualInterest, int t_numOfYears);

private:
	const int MENULENGTH = 62;		//Standard length for menu "graphics"
	double m_currentInterest;		//Monetary amount of interest after calculations
	double m_totalInterest;			//Total accumulated interest
	double m_currentInvestment;		//Current monetary investment
	int m_numOfMonths;				//Number of months given the number of years


};

#endif
#include <iostream>
#include <iomanip>
#include "Calculator.h"

/*
 *	Calculate interest WITHOUT monthly deposit, then print
 */

void Calculator::interestWithoutMonthly(double t_initInvestment, double t_annualInterest, int t_numOfYears) {

	//Calculate the total number of months given t_numOfYears number of years
	m_numOfMonths = t_numOfYears * 12;

	//Initialize m_currentInterest to the starting amount
	m_currentInvestment = t_initInvestment;

	//Draw result "graphics"
	std::cout << "   Balance and Interest Without Additional Monthly Deposits" << std::endl;
	for (int i = 0; i < MENULENGTH; i++) {
		std::cout << "=";
	}

	//Format menu with year, year end balance, and year end earned interest.
	std::cout << std::endl;
	std::cout << "   Year        Year End Balance     Year End Earned Interest" << std::endl;



	//Calculate interest for each month for the given number of years
	for (int i = 1; i <= m_numOfMonths; i++) {

		//Calculate current interest
		m_currentInterest = (m_currentInvestment) * ((t_annualInterest / 100) / 12);

		//Add calculated current interest to year end earned interest
		m_totalInterest += m_currentInterest;


		//If a year has been calculated, print the balance.
		if (i % 12 == 0) {
			//Print year
			std::cout << std::right << std::setw(7) << i / 12;

			//Format to dollar amount for year end balance and year end interest
			std::cout << std::fixed;
			std::cout << std::setprecision(2);

			//Print year end balance (initial investment + total accumulated interest) at rightmost position of column
			std::cout << std::right << std::setw(24) << m_currentInvestment + m_currentInterest;

			//Print interest accrued so far at rightmost position of column
			std::cout << std::right << std::setw(29) << m_totalInterest << std::endl << std::endl;

			//Reset the total interest accrued to calculate the next year's year end earned interest
			m_totalInterest = 0.0;
		}

		//Update the current deposited amount
		m_currentInvestment += m_currentInterest;
	}
}



/*
 *	Calculate interest WITH monthly deposit, then print
 */

void Calculator::interestWithMonthly(double t_initInvestment, double t_monthlyDeposit, double t_annualInterest, int t_numOfYears) {

	//Calculate the total number of months given t_numOfYears number of years
	m_numOfMonths = t_numOfYears * 12;

	//Calculate starting amount WITH monthly deposit
	m_currentInvestment = t_initInvestment + t_monthlyDeposit;


	//Draw result "graphics"
	std::cout << "    Balance and Interest With Additional Monthly Deposits" << std::endl;
	for (int i = 0; i < MENULENGTH; i++) {
		std::cout << "=";
	}

	//Format menu with year, year end balance, and year end earned interest
	std::cout << std::endl;
	std::cout << "   Year        Year End Balance     Year End Earned Interest" << std::endl;



	//Calculate interest for each month for the given number of years
	for (int i = 1; i <= m_numOfMonths; i++) {

		//Calculate current interest
		m_currentInterest = (m_currentInvestment) * ((t_annualInterest / 100) / 12);
		
		//Add calculated current interest to total collected interest
		m_totalInterest += m_currentInterest;


		//If a year has been calculated, print the balance.
		if (i % 12 == 0) {
			//Print year
			std::cout << std::right << std::setw(7) << i / 12;

			//Format to dollar amount for year end balance and year end interest
			std::cout << std::fixed;
			std::cout << std::setprecision(2);

			//Print year end balance (initial investment + total accumulated interest) at rightmost position of column
			std::cout << std::right << std::setw(24) << m_currentInvestment + m_currentInterest;

			//Print interest accrued so far at rightmost position of column
			std::cout << std::right << std::setw(29) << m_totalInterest << std::endl << std::endl;

			//Reset the total interest accrued to calculate the next year's year end earned interest
			m_totalInterest = 0;
		}

		//Update the current deposited amount
		m_currentInvestment = m_currentInvestment + m_currentInterest + t_monthlyDeposit;
	}
}
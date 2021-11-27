#include <iostream>
#include <limits>
#include<string>

#include "BankingMenu.h"
#include "Calculator.h"

//Draw menu "graphics"
void BankingMenu::drawMenu() {

	while (m_loopCheck != "n" && m_loopCheck != "N") {

		/*
		 *		TOP OF THE MENU
		 */

		 //Draw first line of the menu
		for (int i = 0; i < MENULENGTH; i++) {
			std::cout << "*";
		}
		std::cout << std::endl;

		//Draw first half of the second line of the menu
		for (int i = 0; i < MENUSTARS; i++) {
			std::cout << "*";
		}

		//Draw Menu text
		std::cout << " Data Input ";

		//Draw second half of the second line of the menu
		for (int i = 0; i < MENUSTARS; i++) {
			std::cout << "*";
		}

		//Break for new line
		std::cout << std::endl;



		/*
		 *		USER INPUT
		 */

		 //Prompt user for initial investment amount (double)
		std::cout << "Initial Investment Amount: ";
		std::cin >> m_initInvestment;

		//Error check: if user input is NOT a number, ask for one.
		while (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Please input a number: ";
			std::cin >> m_initInvestment;
		}


		//Prompt user for monthly deposit amount (double)
		std::cout << "Monthly Deposit: ";
		std::cin >> m_monthlyDeposit;

		//Error check: if user input for monthlyDeposit is NOT an integer/decimal number, ask for one.
		while (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Please input a number: ";
			std::cin >> m_monthlyDeposit;
		}


		//Clear input stream
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


		//Prompt user for annual interest percentage (integer)
		std::cout << "Annual Interest Percentage: ";
		std::cin >> m_annualInterest;

		//Error check: if user input for annual interest percentage is NOT an integer, ask for one.
		while (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Please input a number: ";
			std::cin >> m_annualInterest;
		}

		//Clear input stream
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


		//Prompt user for number of years for investment (integer)
		std::cout << "Number of years: ";
		std::cin >> m_numOfYears;

		//Error check: if user input for numOfYears is NOT an integer, ask for one.
		while (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Please input a number: ";
			std::cin >> m_numOfYears;
		}

		//"Press any key to continue..."
		system("pause");
		std::cout << std::endl << std::endl;

		//Calculate interest without the monthly deposit amount
		Calculator().interestWithoutMonthly(m_initInvestment, m_annualInterest, m_numOfYears);

		//Calculate interest with the monthly deposit amount
		Calculator().interestWithMonthly(m_initInvestment, m_monthlyDeposit, m_annualInterest, m_numOfYears);

		//Prompt user if they would like to calculate another interest rate, then check input
		std::cout << "Would you like to do another calculation? [Y]/[N]" << std::endl;
		std::cin >> m_loopCheck;
	}
}
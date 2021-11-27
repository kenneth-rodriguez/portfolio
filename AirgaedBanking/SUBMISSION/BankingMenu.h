#pragma once
#include <string>


#ifndef AIRGEADBANKING_BANKINGMENU_H
#define AIRGEADBANKING_BANKINGMENU_H

//Declarations for the BankingMenu class.
class BankingMenu
{

public:

	void drawMenu();					//Draw menu "graphics"

private:

	//Create variables
	const int MENULENGTH = 62;			//Length of asterisks for the top of the menu
	const int MENUSTARS = 25;			//Length of asterisks for the second row of menu; adds stylistic flair	
	double m_initInvestment = 0.0;		//Amount for the initial investment, initialized at 0.0
	double m_monthlyDeposit = 0.0;		//Amount to be deposited monthly, initialized at 0.0
	int m_annualInterest = 0;			//Annual interest percentage, initialized at 0
	int m_numOfYears = 0;				//Number of years for investment, initialized at 0
	std::string m_loopCheck = "z";		//If loopCheck == "N" or "n", quit the program

};

#endif //
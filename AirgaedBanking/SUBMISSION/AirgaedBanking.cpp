/*
 *  Ken Rodriguez
 *  April 4, 2021
 *  Airgead banking app: An application that will calculate the accumulation of interest
 *  given an initial investment amount, a monthly deposit, the annual interest percentage,
 *  and length of time the user would like the investment kept.
 */

#include <iostream>
#include "BankingMenu.h"

//Main method; executes the BankingMenu function.
int main()
{
    BankingMenu().drawMenu();

    return 0;
}

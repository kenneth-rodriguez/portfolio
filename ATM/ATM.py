import sys

# account balance
account_balance = float(500.25)


# printbalance function
# Rubric: Custom function.
def balance():
    print("Your current balance:\n{:.2f}".format(account_balance))


# deposit function
# Rubric: Custom function.
# Rubric: Function that return a correct output to the script.
# In this case, we input the variable account_balance, we add the user input deposit_amount to account_balance,
# and return an updated account_balance wherever the function was called.
def deposit(x):
    deposit_amount = float(input("How much would you like to deposit today?\n"))
    x += deposit_amount
    print("Deposit was ${:.2f}, current balance is ${:.2f}".format(deposit_amount, x))
    return x


# withdraw function
# Rubric: Custom function.
# Rubric: Function that returns a correct output to the script.
def withdraw(x):
    withdrawal_amount = float(input("How much would you like to withdraw today?\n"))
    # Here, we check user input to see if the withdrawal amount is larger than the parameter "x".
    # If user input withdrawal_amount is greater than parameter "x", return to  
    if withdrawal_amount > x:
        print("${:.2f} is greater than your account balance of ${:.2f}".format(withdrawal_amount, x))
        return x
    # If the user input is lower than the function's parameter,
    else:
        # subtract the user input withdrawal_amount from parameter "x".
        x -= withdrawal_amount
        print("Withdrawal amount was ${:.2f}, current balance is ${:.2f}".format(withdrawal_amount, x))
        # finally, return the parameter.
        return x


# User Input, if/else conditional statement to call function based on user input
quit = False
while quit != True:
  userchoice = input("What would you like to do?\n")

  if (userchoice == "D"):
      # Rubric: Example of inputting a variable that is utilized in a function.
      # Rubric: input the variable account_balance into the function deposit.
      updatedBalance = deposit(account_balance)
      account_balance = updatedBalance
  if (userchoice == "W"):
      # Rubric: Example of inputting a variable that is utilized in a function.
      # Rubric: input the variable account_balance into the function withdraw.
      updatedBalance = withdraw(account_balance)
      account_balance = updatedBalance
  if (userchoice == "B"):
      balance()
  if (userchoice == "Q"):
    quit = True
print("Thank you for banking with us.")
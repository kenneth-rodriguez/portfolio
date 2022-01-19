
'''
Section 1: Collect customer input
'''

# 1) Request Rental code:

# Customer input will determine our rental code here.
# An input of "B" for budget, "D" for daily, and "W" for weekly.
rentalCode = str(input("(B)udget, (D)aily, or (W)eekly rental?\n"))
# Rubric: Take a user's input to set the variable rentalCode as a string.

# 2) Request time period the car was rented.

if rentalCode == "B" or rentalCode == "D":
    rentalPeriod = int(input("Number of Days Rented:\n"))
# Rubric: "if" branch.
elif rentalCode == "W":
    rentalPeriod = int(input("Number of Weeks Rented:\n"))
# Rubric: "elif" branch.

# 3) Set the base charge for the rental type as the variable baseCharge.
#    The base charge is the rental period * the appropriate rate:
budgetCharge = 40.00 # Rental code "B"
dailyCharge = 60.00 # Rental code "D"
weeklyCharge = 190.00 # Rental code "W"
# Rubric: the variables representing rate, budgetCharge, dailyCharge, and weeklyCharge are declared as floats.

if rentalCode == "B":
    baseCharge = rentalPeriod * budgetCharge
elif rentalCode == "D":
    baseCharge = rentalPeriod * dailyCharge
elif rentalCode == "W":
    baseCharge = rentalPeriod * weeklyCharge
# Rubric: the variable baseCharge will change based on rentalCode's value.

# 4) Collect Mileage information:
# a)    Prompt the user to input the starting odometer reading and store it as the variable odoStart
odoStart = int(input("Starting Odometer Reading:\n"))
# Rubric: Take a user's input to save the variable odoStart as an integer.

# b)    Prompt the user to input the ending odometer reading and store it as the variable odoEnd
odoEnd = int(input("Ending Odometer Reading:\n"))

# Check to make sure that the ending odometer is greater than the starting odometer
if odoEnd < odoStart:
    print("Error: Odometer's ending value cannot be less than its starting value.")
    quit()

'''
Section 2: Calculate the costs from the customer input
'''

# 1) Calculate the mileage.
# a)	Calculate the total mileage:
totalMiles = odoEnd - odoStart
# Rubric: Modify the variable odoEnd by using the minus operator to subtract the variable odoStart.
# Rubric: After subtracting odoStart from odoEnd, save the difference as the variable totalMiles.

# 2) Calculate the mileage charge and store it as the variable mileCharge:
# a)    Code 'B' (budget) mileage charge: $0.25 for each mile driven
if rentalCode == "B":
    mileCharge = 0.25 * totalMiles

# b)    Code 'D' (daily) mileage charge: no charge if the average
#   number of miles driven per day is 100 miles or less;
#   i)  Calculate the averageDayMiles (totalMiles/rentalPeriod)
#   ii) If averageDayMiles is above the 100 mile per day
#       limit:
#     (1)	calculate extraMiles (averageDayMiles  - 100)
#     (2)	mileCharge is the charge for extraMiles, $0.25 for each mile
if rentalCode == "D":
    averageDayMiles = totalMiles / rentalPeriod
    # Nested IFs
    if averageDayMiles <= 100:
        mileCharge = 0
    else:
        extraMiles = averageDayMiles - 100
        mileCharge = 0.25 * extraMiles
        # Mile charge per day = 0.25 * extraMiles

# c)    Code 'W' (weekly) mileage charge: no charge if the
#   average number of miles driven per week is 900 miles or less;
#   i)	Calculate the averageWeekMiles (totalMiles/ rentalPeriod)
#   ii)	mileCharge is $100.00 per week if the average number of miles driven per week exceeds 900 miles
if rentalCode == "W":
    averageWeekMiles = totalMiles / rentalPeriod
    # Nested IFs
    if averageWeekMiles <= 900:
        mileCharge = 0
    else:
        mileCharge = 100 * rentalPeriod
# Rubric: "else" branch.

'''
Section 3: Display the results to the customer
'''

# 1) Calculate the Amount Due as the variable amtDue
amountDue = baseCharge + mileCharge

# 2) Display the results of the rental calculation in the following order:
# "Rental Summary", Rental code, rental period, starting odometer, ending odometer, miles driven, and amount due.
print("Rental Summary")
print("Rental Code: " + rentalCode)
print("Rental Period: " + str(rentalPeriod))
print("Starting Odometer: " + str(odoStart))
print("Ending Odometer: " + str(odoEnd))
print("Miles Driven: " + str(totalMiles))
print("Amount Due: ${:.2f}".format(amountDue))

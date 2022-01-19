# Define the empty dictionary "grocery_item"
# Rubric: Example of creating a dictionary.
grocery_item = {}
# Define the empty list "grocery_history"
# Rubric: Example of creating a list.
grocery_history=[]
# Define variable "stop" used to check if the while loop condition is met.
stop = 'go'

'''
Section 1 - User Input
'''

# Creation of the "while" loop. While stop is not equal to q, loop.
# Rubric: Example of a while loop structure.
while stop != 'q' :

    # Accept input of the name of the grocery item purchased.
    item_name = input("Item name:\n")    
    # Accept input of the quantity of the grocery item purchased.
    quantity = int(input("Quantity purchased:\n"))
    # Accept input of the cost of the grocery item input (this is a per-item cost).
    cost = float(input("Price per item:\n"))

    # Using the update function to create a dictionary entry which contains the name, number and price entered by the user.
    # Rubric: Example of adding key-value pairs; for example, the key 'name' paired with value item_name.
    grocery_item['name'] = item_name
    grocery_item['number'] = quantity
    grocery_item['price'] = cost
    
    # Add the dictionary grocery_item to the grocery_history list using the append function
    # Rubric: Example of adding data to a list.
    grocery_history.append(grocery_item.copy())
    
    #Accept input from the user asking if they have finished entering grocery items.
    stop = input("Would you like to enter another item? \nType 'c' for continue or 'q' to quit:\n")

# Define variable to hold grand total called 'grand_total'
grand_total = 0

'''
Section 2 - loop through the grocery list
                and
Section 3 - provide output to the console
'''

# "for" loop: for every dictionary in the list grocery_history, loop. 
# Rubric: Example of accessing values in a list; specifically the grocery_item dictionaries in the list grocery_history.
# Rubric: Example of an index-based or range for loop.
for index, item in enumerate(grocery_history):
  
  # Calculate the total cost for the grocery_item.
  # Rubric: Example of accessing values in a dictionary using their respective keys, 'number' and 'price'.
  # Rubric: Example of modifying dictionary values and saving them to the variable item_total.
  item_total = item['number'] * item['price']
  # Add the item_total to the grand_total
  grand_total = grand_total + item_total

  # Output grocery list information in the following order:
  # Quantity, grocery item name, cost of the individual grocery item, and total cost of the item type and quantity. 
  print('%d %s @ $%.2f ea $%.2f' % (item['number'], item['name'], item['price'], item_total))
  
  # Set the item_total equal to 0
  item_total = 0

# Print the grand total
print("Grand total: $%.2f" % grand_total)
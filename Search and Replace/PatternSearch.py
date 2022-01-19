import re

# Paragraph provided for search and replace

lorem_ipsum = '''Lorem ipsum dolor sit-amet, consectetur adipiscing elit. Phasellus iaculis velit ac nunc interdum tempor. 
Ut volutpat elit metus, vel auctor enim commodo at. Nunc quis quam non ligula ultricies luctus porta id justo. 
Quisque dapibus est ut sagittis bibendum. Mauris ullamcorper pellentesque porttitor. Ut sit:amet ex nec dolor gravida 
porttitor. Proin at justo finibus justo vestibulum congue. Suspendisse et ipsum et ipsum eleifend dapibus a fermentum 
lacus. Vivamus porta nunc eu nisl sagittis, quis vulputate metus dignissim. Integer non fermentum nisl, id vestibulum 
elit. Sed euismod vestibulum purus ut porttitor. Integer sit-amet mollis neque. Donec sed lacinia diam, ac finibus 
lectus. Mauris tempor ipsum nisl, vitae posuere est lacinia nec. Nam eget euismod odio.'''


### Section 1: Finding non-alphanumeric characters


# Search criteria variable "regex" contains all characters EXCEPT alphanumeric characters
# Rubric: Example of a search using literal characters in script.
# Rubric: Example of a search for ranges in script.
regex = "[^a-zA-Z0-9\d]"

# Search for all non-alphanumeric characters "regex" from range of a to z, capital A to capital Z, and numbers 0 to 9
# in string "lorem_ipsum". Results are then stored in variable "results".
results = re.findall(regex, lorem_ipsum)

# Print the number of occurrences of all non-alphanumeric characters in string "lorem_ipsum"
print(len(results))


### Section 2: Finding all instances of "sit-amet" and "sit:amet"


# Search criteria variable "regex" contains "sit-amet" and "sit:amet"
# Rubric: Example of a search for sequences in a script.
# Rubric: Example of a use of a search for wildcards in script.
regex = " sit*"

# Search for all instances of "sit-amet" and "sit:amet" in string "lorem_ipsum" and store results in
# the variable "occurrences_sit_amet"
occurrences_sit_amet = re.findall(regex, lorem_ipsum)

# Print the number of times "sit-amet" and "sit:amet" appear in string "lorum_ipsum"
print(len(occurrences_sit_amet))


### Section 3: Replacing instances of "sit-amet" and "sit:amet" with "sit amet"


# Search criteria variable "regex" contains "sit-amet" and "sit:amet"
# Rubric: Example of a use of a search for special characters in script.
regex = "sit[-:]amet"

# Replace "sit:amet" and "sit-amet" in string "lorem_ipsum" with "sit amet" using the sub function, then
# assign the outcome to a variable named "replace_results"
replace_results = re.sub(regex, "sit amet", lorem_ipsum)

# Using the findall function, get all of the instances of "sit amet" in the string assigned to "replace_results"
# Assign the outcome to a variable named "occurrences_sit_amet"
occurrences_sit_amet = re.findall(regex, lorem_ipsum)

# Print the number of occurrences of "sit amet" in string "lorem_ipsum"
print(len(occurrences_sit_amet))
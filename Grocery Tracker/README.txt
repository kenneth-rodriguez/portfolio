Ken Rodriguez
April 21, 2021
CS-210 Foundations in Application Development

- Summary:
This application takes a text file (in this case, CS210_Project_Three_Input_File.txt), collects
each unique word, and calculates how many times those words appear in the document for the purpose
of tracking inventory for a hypothetical corner grocer. The processed data can be printed in one
of three ways, depending on user input: a list of each unique word and the number of times they 
appear, a user-specified item and its number of occurrences, or a histogram of each item's number
of appearances.


- What did you do particularly well?
I believe this application is a good demonstration of my ability to format data, both when printed
and written to a document. When processing the histogram, Python is used to write a document
containing each word and their occurrences; this is written in a way that was easy to parse with C++
and easy to read on its own. The histogram is then printed in an orderly manner, it's clear where it
begins and which data values are higher than others.


- Where could you enhance your code?
The most obvious thing to me would be moving most of the data processing tasks from the user input
switch statement to its own class; this would improve readability and make it easier to modify those
chunks of code in the event that the application needed to be scaled. This could also provide more
opportunities for encapsulation, improving data security.


- Which pieces of the code did you find most challenging to write, and how did you overcome this?
While a simple problem, I had the most trouble writing the contents of the dictionary that contained
the key-value pairs for item names and appearances to a document, here named "frequency.dat".
Initially, I had attempted to write the dictionary straight to the document, which did produce a list,
but that list was a single line with a lot of punctuation; probably more effort to read than was
needed. I decided to write the key-value pairs line-by-line to the document, which greatly improved
readability for both the user and the application. Poring over documentation and W3schools references
was instrumental for determining how best to convert that data to strings and write to a document.


- What skills from this project will be particularly transferable to other projects or course work?
- How did you make the program maintainable, readable, and adaptable?
In addition to reinforcing using methods between classes, this assignment was great practice for
incorporating multiple languages in a single application. Separating big chunks of code into their
own methods and classes is very useful for keeping an application easy to read and easy to maintain
(and adapt!), and will certainly be used in projects moving forward. Writing programs that utilize
multiple languages will also come in especially handy; with the vast array of tools that a language
like Python can offer, it seems almost necessary to implement other languages for large scale tasks.
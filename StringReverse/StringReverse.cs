using System;
using System.Collections.Generic;
using System.Text;

namespace StringReverse
{
    class StringManip
    {
        //Prompt input, collect a string, then return it.
        public string collectedData()
        {

            Console.WriteLine("What string would you like to reverse?");
            string collectedData = Console.ReadLine();
            return collectedData;
        }

        //Reverse an inputted string.
        public string stringReversal(string toReverse)
        {
            //Create a blank string that will hold the reversed characters
            string reversedString = "";
 
            //Starting with the last character, add characters to reversedString
            //until all characters have been added in reverse.
            int length = toReverse.Length - 1;
            while (length >= 0)
            {
                reversedString = reversedString + toReverse[length];
                length--;
            }

            Console.WriteLine("The reversed string is:");
            Console.WriteLine(reversedString);

            return reversedString;
        }
    }
}
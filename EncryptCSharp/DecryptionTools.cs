using System;
using System.Collections.Generic;
using System.Text;
using System.Text.RegularExpressions;

/*
 * Similarly to our encryption tools, our decryption tools are going to operate
 * with the same variables. For a quick reference,
 *
 * (public key) e = 3
 * (prime numbers as per assignment specifications) p = 3    q = 11
 * (public key) n = pq = 33
 * phi(n) = (p-1)(q-1) = 20
 * 
 * To calculate the private key, Euclid's algorithm was used.
 * (private key) 3^(-1) mod 20 = d = 7
 * 
 * To decrypt with private key 'd', we need to use d as an exponent with our public
 * key 'n' to solve for alphabetical character 'y':
 * 
 * x^d mod n = y
 * 
 * for our program, the equation might look like this:
 * 01^(7) mod 33 = "a"
 */

namespace EncryptCSharp
{
    class DecryptionTools
    {
        public void decryptString()
        {
            string toDecrypt;                                                           //String to decrypt
            string decryptedString = "";                                                //Decrypted string (empty, will be filled
            int privateKey = 7;                                                         //Our private key "d"

            Console.Clear();                                                            //Tidy up the console
            toDecrypt = Console.ReadLine();                                             //Collect value that needs to be decrypted from user

            string[] digits = Regex.Split(toDecrypt, @"\D");                            //Split the string into integers
            
            foreach (string value in digits)                                            //For each value in the array digits, parse if they're viable characters
            {
                int number;                                                             //Number after it's been parsed

                if (int.TryParse(value, out number))                                    //If the current value is a number, decrypt and add to decryptedString.
                {
                    number = (int)(Math.Pow(number, privateKey) % 33);                  //For each number, run the decryption algorithm and hope for the best.

                    switch (number)
                    {
                        case 1:
                            decryptedString += "a";
                            break;
                        case 2:
                            decryptedString += "b";
                            break;
                        case 3:
                            decryptedString += "c";
                            break;
                        case 4:
                            decryptedString += "d";
                            break;
                        case 5:
                            decryptedString += "e";
                            break;
                        case 6:
                            decryptedString += "f";
                            break;
                        case 7:
                            decryptedString += "g";
                            break;
                        case 8:
                            decryptedString += "h";
                            break;
                        case 9:
                            decryptedString += "i";
                            break;
                        case 10:
                            decryptedString += "j";
                            break;
                        case 11:
                            decryptedString += "k";
                            break;
                        case 12:
                            decryptedString += "l";
                            break;
                        case 13:
                            decryptedString += "m";
                            break;
                        case 14:
                            decryptedString += "n";
                            break;
                        case 15:
                            decryptedString += "o";
                            break;
                        case 16:
                            decryptedString += "p";
                            break;
                        case 17:
                            decryptedString += "q";
                            break;
                        case 18:
                            decryptedString += "r";
                            break;
                        case 19:
                            decryptedString += "s";
                            break;
                        case 20:
                            decryptedString += "t";
                            break;
                        case 21:
                            decryptedString += "u";
                            break;
                        case 22:
                            decryptedString += "v";
                            break;
                        case 23:
                            decryptedString += "w";
                            break;
                        case 24:
                            decryptedString += "x";
                            break;
                        case 25:
                            decryptedString += "y";
                            break;
                        case 26:
                            decryptedString += "z";
                            break;
                        case 32:
                            decryptedString += " ";
                            break;
                        default:
                            decryptedString += "";
                            break;
                    }
                    
                }
            }
            Console.WriteLine(decryptedString);
            Console.WriteLine("Press any key to continue...");
            Console.ReadKey();
        }
    }
}

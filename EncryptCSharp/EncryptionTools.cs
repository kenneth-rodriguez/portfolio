using System;
using System.Collections.Generic;
using System.Text;


/*
 * EncryptionTools.encryptString() is used to collect input for a string,
 * then produce encrypted values as per the RSA standard. In this case,
 * (public key) e = 3
 * (prime numbers as per assignment specifications) p = 3    q = 11
 * (public key) n = pq = 33
 * phi(n) = (p-1)(q-1) = 20
 * 
 * To calculate the private key, Euclid's algorithm was used.
 * (private key) 3^(-1) mod 20 = d = 7
 * 
 * To calculate how each alphanumeric character was calculated, a standard
 * alphabet map was used; that is, A = 01, B = 02, C = 03, and so on.
 * 
 * After assigning each character (up to Z) with a number, each letter was
 * passed through the following equation:
 * x^e mod n;
 * 
 * if x = a = 01 and n = 33,
 * 1^3 mod 33 = 01
 * and so on.
 */


namespace EncryptCSharp
{
    class EncryptionTools
    {
        public void encryptString()
        {
            string toEncrypt;
            string encryptedString = "";            //User input to return
            int stringLength;                       //Calculate the length of a string
            int i = 0;                              //iteration variable

            Console.Clear();                        //Tidy up screen

            Console.WriteLine("What string do you want to encrypt?");

            toEncrypt = Console.ReadLine();         //Read user input

            stringLength = toEncrypt.Length;        //Collect length of toEncrypt

            toEncrypt = toEncrypt.ToLower();        //Set toEncrypt to lowercase

            while (i < stringLength)                //For the length of the string, encrypt.
            {
                switch (toEncrypt[i])
                {
                    case 'a':
                        encryptedString += "01 ";
                        i++;
                        break;
                    case 'b':
                        encryptedString += "08 ";
                        i++;
                        break;
                    case 'c':
                        encryptedString += "27 ";
                        i++;
                        break;
                    case 'd':
                        encryptedString += "31 ";
                        i++;
                        break;
                    case 'e':
                        encryptedString += "26 ";
                        i++;
                        break;
                    case 'f':
                        encryptedString += "18 ";
                        i++;
                        break;
                    case 'g':
                        encryptedString += "13 ";
                        i++;
                        break;
                    case 'h':
                        encryptedString += "17 ";
                        i++;
                        break;
                    case 'i':
                        encryptedString += "03 ";
                        i++;
                        break;
                    case 'j':
                        encryptedString += "10 ";
                        i++;
                        break;
                    case 'k':
                        encryptedString += "11 ";
                        i++;
                        break;
                    case 'l':
                        encryptedString += "12 ";
                        i++;
                        break;
                    case 'm':
                        encryptedString += "19 ";
                        i++;
                        break;
                    case 'n':
                        encryptedString += "05 ";
                        i++;
                        break;
                    case 'o':
                        encryptedString += "09 ";
                        i++;
                        break;
                    case 'p':
                        encryptedString += "04 ";
                        i++;
                        break;
                    case 'q':
                        encryptedString += "29 ";
                        i++;
                        break;
                    case 'r':
                        encryptedString += "24 ";
                        i++;
                        break;
                    case 's':
                        encryptedString += "28 ";
                        i++;
                        break;
                    case 't':
                        encryptedString += "14 ";
                        i++;
                        break;
                    case 'u':
                        encryptedString += "21 ";
                        i++;
                        break;
                    case 'v':
                        encryptedString += "22 ";
                        i++;
                        break;
                    case 'w':
                        encryptedString += "23 ";
                        i++;
                        break;
                    case 'x':
                        encryptedString += "30 ";
                        i++;
                        break;
                    case 'y':
                        encryptedString += "16 ";
                        i++;
                        break;
                    case 'z':
                        encryptedString += "20 ";
                        i++;
                        break;
                    case ' ':
                        encryptedString += "32 ";
                        i++;
                        break;
                    default:
                        encryptedString += " ";
                        i++;
                        break;
                }            //Depending on the character, encrypt
            }

            Console.WriteLine(encryptedString);
            Console.WriteLine("Press any key to continue...");
            Console.ReadKey();
        }
    }
}

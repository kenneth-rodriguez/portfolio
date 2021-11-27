using System;
using System.Collections.Generic;
using System.Text;

namespace EncryptCSharp
{
    class DrawMenu
    {
        int menuLoop { get; set; }                                              //Menu loop variable
        string menuInput { get; set; }                                          //Collect user's selection
        string anyKey { get; set; }                                             //Save the "press any key" message to streamline things a bit

        public void menuGraphics()                                              //Menu graphics method: print menu graphics
        {
            menuLoop = 0;
            while (menuLoop != 1)                                               //Loop until menuLoop = 1
            {
                Console.Clear();
                Console.WriteLine("What would you like to do?");
                Console.WriteLine("[1] Encrypt a String with default public key");
                Console.WriteLine("[2] Decrypt a String with default public key");
                Console.WriteLine("[3] Quit");

                menuInput = Console.ReadLine();                                 //Collect user input
                int menuSelection;
                anyKey = "Press any key to continue...";


                if (int.TryParse(menuInput, out menuSelection)){

                    switch (menuSelection)
                    {
                        //Case 1: encrypt a user-inputted string
                        case 1:
                            EncryptionTools encryptor = new EncryptionTools();
                            encryptor.encryptString();
                            break;
                        //Case 2: decrypt a user-inputted string
                        case 2:
                            DecryptionTools decryptor = new DecryptionTools();
                            decryptor.decryptString();
                            break;
                        //Case 3: quit
                        case 3:
                            menuLoop = 1;
                            break;
                        //Default case: error check
                        default:
                            Console.WriteLine("Please input a valid integer.\n");
                            Console.WriteLine(anyKey);
                            Console.ReadKey();
                            break;
                    }
                }
                else
                {
                    Console.WriteLine("Please input a valid integer.");
                    Console.WriteLine(anyKey);
                    Console.ReadKey();
                }
            }
        }
    }
}

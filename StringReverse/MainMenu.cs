using System;
using System.Collections.Generic;
using System.Text;

namespace StringReverse
{
    class MainMenu
    {
        //Persistent data
        private string userInput { get; set; }
        private string menuSelect { get; set; }
        private bool menuLoop { get; set; }

        //Draw the "Main" menu.
        public void MenuUI()
        {
            //Declare objects and temporary variables
            StringManip stringTools = new StringManip();
            int menuInteger = 0;

            //Define private variables
            userInput = "no input";
            menuSelect = "no input";
            menuLoop = false;

            while (!menuLoop)
            {
                Console.WriteLine("[1] Collect string input");
                Console.WriteLine("[2] Reverse collected string");
                Console.WriteLine("[3] Print collected or reversed string");
                Console.WriteLine("[4] Quit");

                menuSelect = Console.ReadLine();

                //Check if menuSelect is an integer. if so, accept input, then
                //perform the appropriate task.
                if (int.TryParse(menuSelect, out menuInteger))
                {
                    switch (menuInteger)
                    {
                        //Clear the console, then collect a string to reverse.
                        case 1: Console.Clear(); userInput = stringTools.collectedData(); break;
                        //Clear the console, then reverse collected string.
                        case 2: Console.Clear(); userInput = stringTools.stringReversal(userInput); break;
                        //Clear the console, then print collected string.
                        case 3: Console.Clear(); Console.WriteLine("The current string is:"); Console.WriteLine(userInput); break;
                        //Quit.
                        case 4: menuLoop = true; break;
                        //Default: Clear the console, then tell user that the input is not valid.
                        default: Console.Clear(); Console.WriteLine("Invalid input."); break;
                    }
                }
                //If menuSelect is not an integer, prompt correct input.
                else {   Console.WriteLine("Invalid input.");    }
            }
        }
    }
}

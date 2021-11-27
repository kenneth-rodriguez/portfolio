using System;

namespace EncryptCSharp
{
    class Program
    {
        static void Main(string[] args)
        {
            DrawMenu userMenu = new DrawMenu();
            userMenu.menuGraphics();
        }
    }
}

//Notes:
/*
n = pq

p = 3, q = 11, n = 33

phi(n) = (3 - 1)(11 - 1) = 20

e = 3

choose an integer e such that 1 < e < phi(n) and e and phi(n) are coprime

coprime = their greatest common factor is 1
AKA relatively prime or mutually prime
it's fine though, we already have 'e' (set by assignment)

determine d as e^(-1)mod phi(n); that is d is the multiplicative inverse of e(modulo phi(n)). d is kept as the private key

private key "d" is 7

for more information:
http://ime.math.arizona.edu/g-teams/Profiles/AG/RSA_Encryption.pdf
*/
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    string plaintext;
    int key;

    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");

        return 1;
    }
    else
    {
        if (only_digits(argv[1]) == false)
        {
            printf("Usage: ./caesar key\n");

            return 1;
        }

        key = atoi(argv[1]);
        plaintext = get_string("plaintext: ");
        printf("ciphertext: ");

        for (int i = 0; i < strlen(plaintext); i++)
        {
            char cipher_text = rotate(plaintext[i], key);
            printf("%c", cipher_text);
        }
        printf("\n");

        return 0;
    }
}

// Function that checks if the input is exclusively numerical digits
bool only_digits(string s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        if (isdigit(s[i]) == false)
        {
            return false;
        }
    }
    return true;
}

// Function to rotate the ASCII value of the inputted character by a value n
char rotate(char c, int n)
{
    int ascii_upper_start = 65;
    int ascii_upper_end = 90;
    int ascii_lower_start = 97;
    int ascii_lower_end = 122;
    int alphabet = 26;
    int cipher = 0;

// If the inputted offset is greater than the number of letters in the
// alphabet give the remainder for the wrap around
    if (n > alphabet)
    {
        n = n % alphabet;
    }

    if (isalpha(c))
    {
        if (isupper(c))
        {
            cipher = (int)c + n;
            if (cipher > ascii_upper_end)
            {
                cipher = (cipher - ascii_upper_end - 1) + ascii_upper_start;
            }
        }
        else if (islower(c))
        {
            cipher = (int)c + n;
            if (cipher > ascii_lower_end)
            {
                cipher = (cipher - ascii_lower_end - 1) + ascii_lower_start;
            }
        }
    }
    else
    {
        cipher = (char)c;
    }

    return cipher;
}

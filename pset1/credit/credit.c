#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void)
{
    long long card_number;
    int card_type;
    int digit;
    int even;
    int even_sum = 0;
    int i = 0;
    int odd_sum = 0;

    card_number = get_long("Number: ");

    // The loop finds out the length of the card while doing Luhn's Algorithm
    while (card_number > 0)
    {
        i++;

        if (i % 2 == 0)
        {
            digit = card_number % 10;
            card_number /= 10;
            //printf("Card Number: %ld\n", card_number);
            even = digit * 2;

            // If the product is over 10 separate the two digits and add together
            if (even >= 10)
            {
                even_sum += even % 10;
                even_sum += even / 10;
            }
            else
            {
                even_sum += even;
            }
        }
        else
        {
            odd_sum += card_number % 10;
            card_number /= 10;
            //printf("Card Number: %ld\n", card_number);
        }

        // Probably a stupid way to catch the first two digits of the card number while doing this loop
        if (card_number <= 99 && card_number >= 10)
        {
            card_type = card_number;
        }

        //printf("Even sum: %d\n", even_sum);
        //printf("Odd sum: %d\n", odd_sum);
    }

    int checksum = (even_sum + odd_sum) % 10;

    // Checking if the checksum is valid and the card lengths are valid
    if (checksum == 0 && i > 12 && i < 17 && i != 14)
    {
        if (card_type == 34 || card_type == 37)
        {
            printf("AMEX\n");
        }
        else if (card_type >= 40 && card_type <= 49)
        {
            printf("VISA\n");
        }
        else if (card_type >= 51 && card_type <= 55)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
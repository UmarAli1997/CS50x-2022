#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void)
{
    float n;
    int coins = 0;

    do
    {
        n = get_float("Change owed: ");
    }
    while (n < 0);

    n = round(n * 100);

    while (n > 0)
    {
        while (n >= 25)
        {
            float m = n;
            int old_coins = coins;
            n = round(n - 25);
            if (n < 0)
            {
                n = m;
                coins = old_coins;
            }
            else
            {
                coins++;
            }

        }
        while (n >= 10)
        {
            float m = n;
            int old_coins = coins;
            n = round(n - 10);

            if (n < 0)
            {
                n = m;
                coins = old_coins;
            }
            else
            {
                coins++;
            }
        }

        while (n >= 5)
        {
            float m = n;
            int old_coins = coins;
            n = round(n - 5);

            if (n < 0)
            {
                n = m;
                coins = old_coins;
            }
            else
            {
                coins++;
            }
        }

        while (n >= 1)
        {
            float m = n;
            int old_coins = coins;
            n = round(n - 1);

            if (n < 0)
            {
                n = m;
                coins = old_coins;
            }
            else
            {
                coins++;
            }
        }
    }
    printf("%d\n", coins);
}

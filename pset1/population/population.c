#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;
    int i;
    int j;

    do
    {
        n = get_int("Starting size: ");

    }
    while (n < 9);

    do
    {
        j = get_int("End size: ");

    }
    while (j < n);

    for (i = 0; n < j; i++)
    {
        int ni = n / 3;
        int nj = n / 4;

        n = n + ni - nj;
    }

    printf("Years: %d\n", i);
}
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;

    //Take a positive integer from the user
    do
    {
        height = get_int("Height: ");
    }
    while (1 > height || height > 8);

    //main loop
    for (int i = 0; i < height; i++)
    {
        //Creates the left alignment with spaces
        for (int j = height - 1; j > i; j--)
        {
            printf(" ");
        }

        for (int k = -1; k < i; k++)
        {
            printf("#");
        }
        printf("  ");

        for (int n = -1; n < i; n++)
        {
            printf("#");
        }
        printf("\n");
    }
}

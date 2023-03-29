#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    int layer;

    //Take a positive integer from the user
    do
    {
        height = get_int("Height: ");
    }
    while (0 > height || height > 9);

    for(int row = 0; row < (height); row++)
    {
        for(int col = 0; col < (2 * height + 1 ); col++)
        {
            if(col == (height))
                {
                    printf("  ");
                }
                else
                {
                    printf("#");
                }
        }

        printf("\n");
    }
}



/*
        {
            for (layer = 0; height - 1; layer++)
            {
                if(layer < height)
                {
                    printf(" ");
                }
                printf("#");
            }

            printf("#");
        }
*/
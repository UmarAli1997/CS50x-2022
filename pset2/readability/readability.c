#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int coleman_liau(string sentence);

int main(void)
{
    string text = get_string("Text: ");

    int index = coleman_liau(text);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", index);
    }
}

int coleman_liau(string text)
{

    int letter = 0;
    int sentence = 0;
    int word = 1;

    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            letter++;
        }
        else if (isspace(text[i]))
        {
            word++;
        }
        else if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentence++;
        }

    }

    //printf("Letters: %d\n", letter);
    //printf("Words: %d\n", word);
    //printf("Sentences: %d\n", sentence);
    float L = letter * 100.0 / word;
    float S = sentence * 100.0 / word;

    float index = 0.0588 * L - 0.296 * S - 15.8;

    //printf("Index: %f\n", index);
    index = round(index);

    return index;
}
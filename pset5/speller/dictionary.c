// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 100000;

// Hash table
node *table[N];

// Variable to track size of dictionary
int dict_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hashing input to find the hash value
    int hash_val = hash(word);
    node *cursor = table[hash_val];

    // Looping through linked list for the corresponding hash value
    while (cursor != NULL)
    {
        // Comparing the words together
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}

// Hashes word to a number
// djb2 hash function
unsigned int hash(const char *word)
{
    unsigned int hash = 5381;
    int c;

    while ((c = tolower(*word++)))
    {
        hash = (((hash << 5) + hash) + c) % N; // hash * 33 + c
    }

    return hash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Opens dictionary file and checks if it has opened properly
    FILE *dict_pointer = fopen(dictionary, "r");
    if (dict_pointer == NULL)
    {
        //printf("Could not load %s. \n", dictionary);
        return false;
    }
    // Defining array to read words into
    char tmp[LENGTH + 1];

    while (fscanf(dict_pointer, "%s", tmp) != EOF)
    {
        node *w = malloc(sizeof(node));
        if (w == NULL)
        {
            //printf("Not enough memory.\n");
            return false;
        }

        // Copy word into node
        strcpy(w->word, tmp);
        w->next = NULL;

        // Get hash value for the word
        int hash_val = hash(tmp);

        // Insert new node into table at the hash value location then
        // change the beginning of the table for the corresponding hash value
        w->next = table[hash_val];
        table[hash_val] = w;

        dict_size++;
    }

    fclose(dict_pointer);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dict_size++;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        // Assign cursor node to each element in the hash table
        node *cursor = table[i];

        while (cursor != NULL)
        {
            // Assign temporary node to cursor
            node *tmp = cursor;
            // Point cursor to next node in linked list
            cursor = cursor->next;
            //Free temporary pointer
            free(tmp);
        }

        // If the cursor = NULL and i = N - 1 then all memory should be freed
        if (i == N - 1 && cursor == NULL)
        {
            return true;
        }
    }
    return false;
}

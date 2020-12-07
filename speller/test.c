// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

//counts numbers of words
long count_words = 0;

// Number of buckets in hash table
const unsigned int N = 26;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;



// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //hash word to obtain a hash value
    int h = hash(word);
    //set a cursor to the head
    node *cursor = table[h];
    //set a temp
    char tempword[LENGTH+1];
    //calculate length of the word
    int templength = strlen(word);
    //array tempword
    for (int x = 0; x < templength ; x++)
    {
        tempword[x] = tolower(word[x]);
    }
    //set the NULL character at the end of the word
    tempword[templength] = '\0';

    //loop until the end of the hash table
    while(cursor != NULL)
    {
        if(strcmp(cursor->word, tempword) == 0)
        {
            cursor = cursor -> next;
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    if (word[0] != '\'')
    {
        return tolower(word[0]) - 'a';
    }
    fprintf(stderr, "first character is '");
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //open and read file
    FILE *file = fopen(dictionary, "r");
    //check for NULL
    if (file == NULL)
    {
        fprintf(stderr, "Could not load dictionary");
        unload();
        return false;
    }


    //read strings from file one at a time
    char word[LENGTH];
    while (fscanf(file, "%s", word) != EOF)
    {
        //call hash function
        int h = hash(word);
        //create nodes
        node *n = malloc(sizeof(node));
        //copy string
        strcpy(n-> word, word);
        //set pointer to NULL
        n-> next = NULL;
        if (n == NULL)
        {
            unload();
            return false;
        }
        //set pointer from new node to where table was pointing
        n -> next = table[h];
        //set pointer from table to the new node
        table[h] = n;

        count_words++;
    }
    fclose(file);
    return true;

}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return count_words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    //loop for all characters
    for (int x = 0; x < 27; x++)
    {
        //set a cursor to the head
        node *cursor = table[x];
        while (cursor != NULL)
        {
            //set a temp cursor that equals to the cursor
            node *tmp = cursor;
            //set cursor to next node
            cursor = cursor -> next;
            //free memory
            free(tmp);
        }
    }
    return true;
}

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_num(string x);
int count_word(string x);
int count_sent(string x);

//ask user for input of text
int main(void)
{
    string input = get_string("please enter the text:\n");

// number of letters
    float nchar = count_num(input);
// number of words
    float nword = count_word(input);
// number of sentencess
    float nsent = count_sent(input);

// Index
    float L = nchar / nword * 100;
    float S = nsent / nword * 100;
    int I = round(0.0588 * L - 0.296 * S - 15.8);
    if (I >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (I < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %d\n", I);
    }
}

//counting number of letters
int count_num(string x)
{
    int count, nchar = 0;
    for (count = 0; count < strlen(x); count++)
    {
        if ((x[count] >= 'a' && x[count] <= 'z') || (x[count] >= 'A' && x[count] <= 'Z'))
        {
            nchar++;
        }
    }
    return nchar;
}

//counting words
int count_word(string x)

{
    int count, nchar = 0;
    for (count = 0; count < strlen(x); count++)
    {
        if (x[count] == ' ')
        {
            nchar++;
        }
    }
    if (nchar != 0)
    {
        nchar++;
    }
    return nchar;
}

//counting sentencess
int count_sent(string x)

{
    int count, nchar = 0;
    for (count = 0; count < strlen(x); count++)
    {
        if (x[count] == '.' || x[count] == '!' || x[count] == '?')
        {
            nchar++;
        }
    }
    return nchar;
}
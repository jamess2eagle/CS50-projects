#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, string argv[])
{
// once user input ./caesar number, cheks if the int is positive number
    if (argc == 2)
    {
        int num = atoi(argv[1]);
        if (num <= 0)
        {
            printf("Usage: ./caeser key\n");
            return 0;
        }

// asks user for input
        string text = get_string("Enter Text:\n");
        printf("ciphertext: ");


//converts text into string
        for (int count = 0; count < strlen(text); count++)
        {
            int test = text[count];
            int ascii = test + num;

//converts lower case
            if (test > 96 && test < 123)
            {
                if (ascii >= 123)
                {
                    int num2 = num;
                    do
                    {
                        num2 = num2 - 26;
                    }
                    while (num2 + test >= 123);
                    printf("%c", text[count] + num2);
                }
                else
                {
                    printf("%c", text[count] + num);
                }
            }
//coverts upper case
            else if (test > 64 && test < 91)
            {
                if (ascii >= 91)
                {
                    int num2 = num;
                    do
                    {
                        num2 = num2 - 26;
                    }
                    while (num2 + test >= 91);
                    printf("%c", text[count] + num2);
                }
                else
                {
                    printf("%c", text[count] + num);
                }
            }
            else
            {
                printf("%c", text[count]);
            }
        }
        printf("\n");
// otherwise returns ./caesar key
    }
    else
    {
        printf("Usage: ./caeser key\n");
        return 1;
    }
}
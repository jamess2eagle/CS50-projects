# include <cs50.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

// command line argument
int main(int argc, string argv[])
{

    // test fails
    if (argc != 2)
    {
        printf("./substitution key\n");
        return 1;
    }

// check the count of letters
    int count = strlen(argv[1]);
    string input = argv[1];
    int i = 0, j = 0;

//check if the user input is letters
    for (i = 0; input[i] != '\0'; i++)
    {
        int ascii = input[i];
        if (ascii < 65 || (ascii > 90 && ascii < 97) || ascii > 122)
        {
            printf("./substitution key\n");
            return 1;
        }
    }

//check for duplicate
    for (i = 0; i < 26 ; i++)
    {
        for (j = i + 1; j < 26; j++)
        {
            if (input[i] == input[j])
            {
                printf("./substitution key\n");
                return 1;
            }
        }
    }

    if (argc != 2)
    {
        printf("./substitution key\n");
        return 1;
    }

//checks if the user input 26 letters of command line argument
    else
    {
        if (argc == 2 && count == 26)
        {
            string text = get_string("plaintext: ");
            int count2 = strlen(text);
            for (int x = 0; x < count2 ; x++)
            {
                int ascii2 = text[x];
                // looks for the ascii2'th digit of character in input

                //text is lower case & input is upper case
                if (ascii2 > 96 && ascii2 < 123)
                {
                    ascii2 -= 97;
                    int ascii3 = input[ascii2];
                    if (ascii3 > 64 && ascii3 < 91)
                    {
                        text[x] = input[ascii2] + 32;
                    }

//text is lower case & input is lower case
                    if (ascii3 > 96 && ascii3 < 123)
                    {
                        text[x] = input[ascii2];
                    }
                }
// text is upper case & input is upper case
                if (ascii2 > 64 && ascii2 < 91)
                {
                    ascii2 -= 65;
                    int ascii3 = input[ascii2];
                    if (ascii3 > 64 && ascii3 < 91)
                    {
                        text[x] = input[ascii2];
                    }

// text is upper case & input is lower case
                    if (ascii3 > 96 && ascii3 < 123)
                    {
                        text[x] = input[ascii2] - 32;
                    }
                }
            }
            printf("ciphertext: %s\n", text);

        }


    }
}
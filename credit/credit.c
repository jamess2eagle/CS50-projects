#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //ask user to input the CC number
    long long credit = get_long_long("Enter the number:\n");
    
    int lastdigit = 0, count = 0, dble_odd_number = 0, odd_number = 0, even_number = 0, sum = 0, seconddigit = 0, firsttwo = 0;
    
    //loop that removes a digit until there are no more numbers left
    while (credit > 0)
    {
    //saves 2nd digit before last digit gets replaced
        seconddigit = lastdigit;    
        lastdigit = credit % 10;
    //adds odd & even numbers
        if (count % 2 == 0)
        {
            even_number +=  lastdigit;
        }
        else
        {
            dble_odd_number = lastdigit * 2;
            odd_number += (dble_odd_number / 10 + dble_odd_number % 10) ;
        }
    credit /= 10;
    count++;
    }
    //checking if the number is valid
    sum = even_number + odd_number;
    bool valid = sum % 10 == 0;
    firsttwo = lastdigit * 10 + seconddigit;
    if ((firsttwo == 34 || firsttwo == 37) && count == 15 && valid)
    {
        printf("AMEX\n");
    }
    else if (firsttwo >= 51 && firsttwo <= 55 && count == 16 && valid)
    {
        printf("MASTERCARD\n");
    }
    else if (lastdigit == 4 && count >= 13 && count <= 16 && valid)
    {
        printf("VISA\n");
    }
    else
        printf("INVALID\n");        
    }
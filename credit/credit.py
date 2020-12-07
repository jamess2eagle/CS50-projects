from cs50 import get_int
from cs50 import get_string


cc = get_string("Number: ")
sum = 0
sum2 = 0
# last digit
for i in range(len(cc)-1, -1, -2):
    sum = sum + int(cc[i])

digit1 = 0
digit2 = 0
# 2nd to the last digit
for i in range(len(cc)-2, -1, -2):
    digit1 = int(cc[i]) * 2 // 10
    digit2 = int(cc[i]) * 2 % 10
    # add each digits
    sum2 = sum2 + digit1 + digit2
total_sum = sum + sum2
firsttwo = int(cc[0]) * 10 + int(cc[1])

# checks for valid CC
if(total_sum % 10 != 0):
    print("INVALID")
# checks for AMEX
elif((firsttwo == 34 or firsttwo == 37) and len(cc) == 15):
    print("AMEX")
# checks for MC
elif((firsttwo >= 51 and firsttwo <= 55) and len(cc) == 16):
    print("MASTERCARD")
# checks for Visa
elif(int(cc[0]) == 4 and (len(cc) == 13 or len(cc) == 16)):
    print("VISA")
# else return invalid
else:
    print("INVALID")
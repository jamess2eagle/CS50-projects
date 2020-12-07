from cs50 import get_string
from sys import argv, exit
import csv
import re


# command line argument
for arg in argv:
    data = argv[1]
    sequence = argv[2]

# checks for proper usage
if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

# open data file
file = open(data, "r")
filereader = csv.DictReader(file)

# set fieldname as header
fieldname = filereader.fieldnames
fields = len(fieldname)

# open dna file
dnafile = open(sequence, "r")
dnareader = dnafile.read()

dnacount = {}
# iterate over all fields and count all STR's
for i in range(1, fields):
    length = len(fieldname[i])
    dnacount[fieldname[i]] = 0
    # iterate over all dna file
    for j in range(len(dnareader)):
        count = 0
        # check for consecutive STR's
        while dnareader[j:j+length] == fieldname[i]:
            j += length
            count += 1
        # save the count
        if count > dnacount[fieldname[i]]:
            dnacount[fieldname[i]] = count

# iterate over database
match = False
for row in filereader:
    # iterate and check if the STR's are matching with the DNA file
    for i in range(1, fields):
        # check = true if matches
        if int(row[fieldname[i]]) == int(dnacount[fieldname[i]]):
            check = True
        # breaks if false
        else:
            check = False
            break
    # if true, print name
    if check == True:
        print(row['name'])
        match = True
if match == False:
    print("No match")
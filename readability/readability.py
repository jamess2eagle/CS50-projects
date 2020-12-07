from cs50 import get_string
import re

# asks user for input
txt = get_string("Text: ")
lettercount = 0
# checks for letter count
for letter in txt:
    if letter.isalpha() == True:
        lettercount += 1
print("letter", lettercount)


# checks for words count
words = txt.split()
print("Words", len(words))
wordcount = len(words)


# checks for sentences count
sentences = re.split('[.!?]', txt)
print("Sentences", len(sentences) - 1)
sentencecount = len(sentences) - 1


L = lettercount / wordcount * 100
S = sentencecount / wordcount * 100
index = 0.0588 * L - 0.296 * S - 15.8
print(index)


if index > 15:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print("Grade ", int(round(index)))

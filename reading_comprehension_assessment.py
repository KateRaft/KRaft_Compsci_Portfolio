# Import functions from python library
from library import get_string

# Variable declaration and initialization
letters = 0
words = 1
sentences = 0

# Get text input from user
text = get_string("Text: ")

# Increase each variable if stipulations apply
for element in text:
    if element.isupper():
        letters += 1
    elif element.islower():
        letters += 1
    if element.isspace():
        words += 1
    if (element == "." or element == "!" or element == "?"):
        sentences += 1

# Calculate Reading Grade Level using Coleman-Liau Index
L = letters / words * 100
S = sentences / words * 100

index = (0.0588 * L - 0.296 * S - 15.8)

# Store calculation as new rounded variable
grlvl = round(index)

# Output Grade Level Readability according to stipulations
if grlvl < 1:
    print("Before Grade 1")
elif grlvl > 16:

# Import modules needed
import csv
import library
import sys

# Define own functions

# Define function for calculating longest run of consecutive repeats in DNA sequence
def get_long_run_repeats(txt_reader, STR):

    # Start at ith index and loop until last repeat at position 0th index decrementing i down one each time
    result = [0] * len(txt_reader)
    for i in range(len(txt_reader) - len(STR), -1, -1):
        if txt_reader[i: i + len(STR)] == STR:
            if i + len(STR) > len(txt_reader) - 1:
                # Define base case
                result[i] = 1
            else:
                result[i] = 1 + result[i + len(STR)]
    return max(result)

# Define function for matching STR counts against each row in CSV file
def compare_match(csv_reader, array):
    for row in csv_reader:
        person_id = row[0]
        # Slice row from first row (after person_id row) to end row
        numbers = [int(val) for num in row[1:]]
        if numbers == array:
            print(person_id)
            return
        else:
            print("No match")

## Define main
def main():

# Command-line arguments specifications
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")

# Give command-line arguments descriptive names
    database = sys.argv[1]
    sequence = sys.argv[2]

# Open CSV file as dictionary and read contents into memory
# Save STR counts in data structure
    with open(database, "r") as csv_file:
        fieldnames = ['']
        csv_reader = csv.DictReader(csv_file)
        DNA_sequences = next(csv_reader)

# Open DNA sequence as string and read contents into memory
    with open(sequence, "r") as txt_file:
        txt_reader = csv.reader(txt_file)

# For each STR, compute the longest run of consecutive repeats in DNA sequence
# "array" holds values for maximum number of times each sequence repeats in string
        array = [get_long_run_repeats(txt_reader, STR) for seq in DNA_sequences]

# Compare the STR counts against each row in the CSV file
# Print out match's name (if one exists)
    compare_match(csv_reader, array)


if __name__ == "__main__":
    main()

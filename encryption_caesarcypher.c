#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Check Argument Validity
int main(int argc, string argv[])
{
    // If user input two command-lines arguments
    if (argc == 2)
    {
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            // Check if each character in string is decimal digit (0 is equivalent to boolean false)
            if (isdigit(argv[1][i]) == 0)
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
    }

    // If user did not input two command-line arguments
    else if (argc != 2)
    {
        printf("Error: need two command-line arguments\n");
        return 1;
    }

    // Convert string input to integer
    int k = atoi(argv[1]);

    // Prompt user for plaintext to be converted
    string plaintext = get_string("Plaintext: ");

    // Cast "integer" inputs as chars and convert plaintext to ciphertext
    printf("Ciphertext: ");

    for (int j = 0, length = strlen(plaintext); j < length; j++)
    {
        char p = plaintext[j];

        if (isalpha(p))
        {
            if (isupper(p))
            {
                printf("%c", (p - 65 + k) % 26 + 65);
            }
            else if (islower(p))
            {
                printf("%c", (p - 97 + k) % 26 + 97);
            }
        }
        else
        {
            printf("%c", p);
        }
    }
    printf("\n");
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //including all the libraries of c language

#define MAX_SIZE 100 // maximum size of the array is 100

// Function to perform CRC division
void CRC_operation(char *message, char *polynomial, char *remainder)
{
    int message_size = strlen(message);
    int polynomial_size = strlen(polynomial);

    // Make a copy of the message
    char temp[MAX_SIZE];
    strcpy(temp, message);

    // Append zeros to the temp message based on polynomial length
    for (int i = 0; i < polynomial_size - 1; i++)
    {
        strcat(temp, "0");
    }

    // Perform CRC division
    for (int i = 0; i < message_size; i++)
    {
        if (temp[i] == '1')
        {
            for (int j = 0; j < polynomial_size; j++)
            {
                if (temp[i + j] == polynomial[j])
                    temp[i + j] = '0';
                else
                    temp[i + j] = '1';
            }
        }
    }

    // Copy the remainder to the output
    strcpy(remainder, temp + message_size);
}

int main()
{
    char sender_message[MAX_SIZE];
    char receiver_message[MAX_SIZE];
    char polynomial_bits[MAX_SIZE];
    char sender_checksum[MAX_SIZE];
    char receiver_checksum[MAX_SIZE];

    // Input number of bits
    int bit_count;
    printf("Enter the number of bits: ");
    scanf("%d", &bit_count);

    // Input sender message
    printf("Enter the sender message : ", bit_count);
    scanf("%s", sender_message);

    // Input polynomial
    printf("Enter the polynomial : ");
    scanf("%s", polynomial_bits);

    // Input received message
    printf("Enter the received message : ", bit_count);
    scanf("%s", receiver_message);

    // Perform CRC for sender message
    CRC_operation(sender_message, polynomial_bits, sender_checksum);

    // Perform CRC for receiver message
    CRC_operation(receiver_message, polynomial_bits, receiver_checksum);

    // Check if sender message and receiver message are equal
    if (strcmp(sender_checksum, receiver_checksum) == 0)
    {
        printf("Codeword at sender side: %s\n", sender_checksum);
        printf("Codeword at receiver side: %s\n", receiver_checksum);
        printf("No error detected.\n");
    }
    else
    {
        printf("Codeword at sender side: %s\n", sender_checksum);
        printf("Codeword at receiver side: %s\n", receiver_checksum);
        printf("Error detected.\n");
    }

    return 0;
}

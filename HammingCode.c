// #include <stdio.h>
// // Function to calculate the parity bit
// int calculateParityBit(int data[], int n, int parityIndex)
// {
//     int count = 0;
//     for (int i = 0; i < n; i++)
//     {
//         if (data[i] == 1 && ((i + 1) & (1 << parityIndex)) != 0)
//         {
//             count++;
//         }
//     }
//     return count % 2;
// }
// // Function to perform error correction
// void performErrorCorrection(int receivedData[], int n, int numParityBits)
// {
//     int errorPosition = 0;
//     for (int i = 0; i < numParityBits; i++)
//     {
//         errorPosition += (receivedData[(1 << i) - 1] << i);
//     }
//     if (errorPosition != 0)
//     {
//         printf("Error at Position %d\n", errorPosition);
//         // Correct the error bit
//         receivedData[errorPosition - 1] = receivedData[errorPosition - 1] == 0 ? 1 : 0;
//     }
//     else
//     {
//         printf("No error detected.\n");
//     }
// }
// int main()
// {
//     int numBits;
//     printf("No. of bits: ");
//     scanf("%d", &numBits);
//     int sendData[numBits];
//     printf("Send Data: ");
//     for (int i = 0; i < numBits; i++)
//     {
//         scanf("%1d", &sendData[i]);
//     }
//     int receivedData[numBits];
//     printf("Received Data: ");
//     for (int i = 0; i < numBits; i++)
//     {
//         scanf("%1d", &receivedData[i]);
//     }
//     // Calculate the number of parity bits required
//     int numParityBits = 0;
//     while ((1 << numParityBits) < (numBits + numParityBits + 1))
//     {
//         numParityBits++;
//     }
//     // Insert parity bits at their respective positions in the send data
//     int codeword[numBits + numParityBits];
//     int dataIndex = 0;
//     int codewordIndex = 0;
//     for (int i = 0; i < numBits + numParityBits; i++)
//     {
//         if ((i + 1) == (1 << dataIndex))
//         {
//             codeword[i] = 0;
//             dataIndex++;
//         }
//         else
//         {
//             codeword[i] = sendData[codewordIndex];
//             codewordIndex++;
//         }
//     }
//     // Calculate parity bits
//     for (int i = 0; i < numParityBits; i++)
//     {
//         codeword[(1 << i) - 1] = calculateParityBit(codeword, numBits + numParityBits, i);
//     }
//     printf("Codeword at Sender Side: ");
//     for (int i = 0; i < numBits + numParityBits; i++)
//     {
//         printf("%d", codeword[i]);
//     }
//     printf("\n");
//     printf("Codeword at Receiver Side: ");
//     for (int i = 0; i < numBits; i++)
//     {
//         printf("%d", receivedData[i]);
//     }
//     for (int i = 0; i < numParityBits; i++)
//     {
//         printf("%d", codeword[(1 << i) - 1]);
//     }
//     printf("\n");
//     // Perform error detection and correction
//     performErrorCorrection(receivedData, numBits, numParityBits);
//     printf("Corrected Data: ");
//     for (int i = 0; i < numBits; i++)
//     {
//         printf("%d", receivedData[i]);
//     }
//     printf("\n");
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //including all the libraries of c language

#define MAX_SIZE 100 // maximum size of the array is 100

// Function to perform CRC division
void performCRC(char *message, char *polynomial, char *remainder)
{
    int messageLen = strlen(message);
    int polynomialLen = strlen(polynomial);

    // Make a copy of the message
    char temp[MAX_SIZE];
    strcpy(temp, message);

    // Append zeros to the temp message based on polynomial length
    for (int i = 0; i < polynomialLen - 1; i++)
    {
        strcat(temp, "0");
    }

    // Perform CRC division
    for (int i = 0; i < messageLen; i++)
    {
        if (temp[i] == '1')
        {
            for (int j = 0; j < polynomialLen; j++)
            {
                if (temp[i + j] == polynomial[j])
                    temp[i + j] = '0';
                else
                    temp[i + j] = '1';
            }
        }
    }

    // Copy the remainder to the output
    strcpy(remainder, temp + messageLen);
}

int main()
{
    char senderMessage[MAX_SIZE];
    char receiverMessage[MAX_SIZE];
    char polynomial[MAX_SIZE];
    char senderRemainder[MAX_SIZE];
    char receiverRemainder[MAX_SIZE];

    // Input number of bits
    int numBits;
    printf("Enter the number of bits: ");
    scanf("%d", &numBits);

    // Input sender message
    printf("Enter the sender message (in binary, %d bits): ", numBits);
    scanf("%s", senderMessage);

    // Input polynomial
    printf("Enter the polynomial (in binary): ");
    scanf("%s", polynomial);

    // Input received message
    printf("Enter the received message (in binary, %d bits): ", numBits);
    scanf("%s", receiverMessage);

    // Perform CRC for sender message
    performCRC(senderMessage, polynomial, senderRemainder);

    // Perform CRC for receiver message
    performCRC(receiverMessage, polynomial, receiverRemainder);

    // Check if sender message and receiver message are equal
    if (strcmp(senderRemainder, receiverRemainder) == 0)
    {
        printf("Codeword at sender side: %s\n", senderRemainder);
        printf("Codeword at receiver side: %s\n", receiverRemainder);
        printf("No error detected.\n");
    }
    else
    {
        printf("Codeword at sender side: %s\n", senderRemainder);
        printf("Codeword at receiver side: %s\n", receiverRemainder);
        printf("Error detected.\n");
    }
    return 0;
}

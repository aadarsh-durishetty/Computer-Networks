#include <stdio.h>
// Function to calculate the parity bit
int calculateParityBit(int data[], int n, int parityIndex)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (data[i] == 1 && ((i + 1) & (1 << parityIndex)) != 0)
        {
            count++;
        }
    }
    return count % 2;
}
// Function to perform error correction
void performErrorCorrection(int receivedData[], int n, int numParityBits)
{
    int errorPosition = 0;
    for (int i = 0; i < numParityBits; i++)
    {
        errorPosition += (receivedData[(1 << i) - 1] << i);
    }
    if (errorPosition != 0)
    {
        printf("Error at Position %d\n", errorPosition);
        // Correct the error bit
        receivedData[errorPosition - 1] = receivedData[errorPosition - 1] == 0 ? 1 : 0;
    }
    else
    {
        printf("No error detected.\n");
    }
}
int main()
{
    int numBits;
    printf("No. of bits: ");
    scanf("%d", &numBits);
    int sendData[numBits];
    printf("Send Data: ");
    for (int i = 0; i < numBits; i++)
    {
        scanf("%1d", &sendData[i]);
    }
    int receivedData[numBits];
    printf("Received Data: ");
    for (int i = 0; i < numBits; i++)
    {
        scanf("%1d", &receivedData[i]);
    }
    // Calculate the number of parity bits required
    int numParityBits = 0;
    while ((1 << numParityBits) < (numBits + numParityBits + 1))
    {
        numParityBits++;
    }
    // Insert parity bits at their respective positions in the send data
    int codeword[numBits + numParityBits];
    int dataIndex = 0;
    int codewordIndex = 0;
    for (int i = 0; i < numBits + numParityBits; i++)
    {
        if ((i + 1) == (1 << dataIndex))
        {
            codeword[i] = 0;
            dataIndex++;
        }
        else
        {
            codeword[i] = sendData[codewordIndex];
            codewordIndex++;
        }
    }
    // Calculate parity bits
    for (int i = 0; i < numParityBits; i++)
    {
        codeword[(1 << i) - 1] = calculateParityBit(codeword, numBits + numParityBits, i);
    }
    printf("Codeword at Sender Side: ");
    for (int i = 0; i < numBits + numParityBits; i++)
    {
        printf("%d", codeword[i]);
    }
    printf("\n");
    printf("Codeword at Receiver Side: ");
    for (int i = 0; i < numBits; i++)
    {
        printf("%d", receivedData[i]);
    }
    for (int i = 0; i < numParityBits; i++)
    {
        printf("%d", codeword[(1 << i) - 1]);
    }
    printf("\n");
    // Perform error detection and correction
    performErrorCorrection(receivedData, numBits, numParityBits);
    printf("Corrected Data: ");
    for (int i = 0; i < numBits; i++)
    {
        printf("%d", receivedData[i]);
    }
    printf("\n");
}
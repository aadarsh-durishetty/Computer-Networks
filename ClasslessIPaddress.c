
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convertIPToBinary(const char *ip, int binaryIP[])
{
    int i = 0;
    char *token = strtok((char *)ip, ".");
    while (token != NULL)
    {
        binaryIP[i++] = atoi(token);
        token = strtok(NULL, ".");
    }
}

char calculateIPClass(const int binaryIP[])
{
    if (binaryIP[0] >= 1 && binaryIP[0] <= 126)
        return 'A';
    else if (binaryIP[0] >= 128 && binaryIP[0] <= 191)
        return 'B';
    else if (binaryIP[0] >= 192 && binaryIP[0] <= 223)
        return 'C';
    else if (binaryIP[0] >= 224 && binaryIP[0] <= 239)
        return 'D';
    else if (binaryIP[0] >= 240 && binaryIP[0] <= 255)
        return 'E';
    else
        return 'X';
}

void calculateBroadcastAddress(const int binaryIP[], const int subnetMask[], int broadcastAddress[])
{
    for (int i = 0; i < 4; i++)
    {
        broadcastAddress[i] = binaryIP[i] | (subnetMask[i] ^ 255);
    }
}

void calculateNetworkAddress(const int binaryIP[], const int subnetMask[], int networkAddress[])
{
    for (int i = 0; i < 4; i++)
    {
        networkAddress[i] = binaryIP[i] & subnetMask[i];
    }
}

int calculateNumSubnets(const int subnetMask[])
{
    int numSubnets = 1;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 7; j >= 0; j--)
        {
            if ((subnetMask[i] >> j) & 1)
            {
                numSubnets <<= 1;
            }
            else
            {
                break;
            }
        }
    }
    return numSubnets;
}

void calculateSubnet1IPRange(const int networkAddress[], const int subnetMask[], int subnet1StartIP[], int subnet1LastIP[])
{
    for (int i = 0; i < 4; i++)
    {
        subnet1StartIP[i] = networkAddress[i];
        subnet1LastIP[i] = networkAddress[i] | (subnetMask[i] ^ 255);
    }
    subnet1StartIP[3] += 1;
    subnet1LastIP[3] -= 1;
}

void printIPAddress(const int ipAddress[])
{
    for (int i = 0; i < 4; i++)
    {
        printf("%d", ipAddress[i]);
        if (i < 3)
        {
            printf(".");
        }
    }
}

int main()
{
    char ip[16];
    int subnetMask[4];
    int binaryIP[4];
    int binarySubnetMask[4];
    int broadcastAddress[4];
    int networkAddress[4];
    int subnet1StartIP[4];
    int subnet1LastIP[4];

    printf("Enter the IP address in dot-decimal notation: ");
    scanf("%15s", ip);

    printf("Enter the subnet mask in dot-decimal notation: ");
    scanf("%d.%d.%d.%d", &subnetMask[0], &subnetMask[1], &subnetMask[2], &subnetMask[3]);

    convertIPToBinary(ip, binaryIP);
    convertIPToBinary(ip, binarySubnetMask);

    calculateBroadcastAddress(binaryIP, subnetMask, broadcastAddress);
    calculateNetworkAddress(binaryIP, subnetMask, networkAddress);
    calculateSubnet1IPRange(networkAddress, subnetMask, subnet1StartIP, subnet1LastIP);

    printf("Class: %c\n", calculateIPClass(binaryIP));
    printf("Broadcast address: ");
    printIPAddress(broadcastAddress);
    printf("\n");
    printf("Network address: ");
    printIPAddress(networkAddress);
    printf("\n");
    printf("Number of subnets: %d\n", calculateNumSubnets(subnetMask));
    printf("Starting IP address of Subnet 1: ");
    printIPAddress(subnet1StartIP);
    printf("\n");
    printf("Last IP address of subnet 1: ");
    printIPAddress(subnet1LastIP);
    printf("\n");
    printf("Usable IP range in subnet 1: ");
    printIPAddress(subnet1StartIP);
    printf(" to ");
    printIPAddress(subnet1LastIP);
    printf("\n");

    return 0;
}
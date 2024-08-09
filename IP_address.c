#include <stdio.h>

int main()
{
    char ip[15];
    printf("Enter an IP address: ");
    scanf("%s", ip);

    // Extracting the first octet from the IP address
    int firstOctet = 0;
    sscanf(ip, "%d", &firstOctet);

    // Determining the class based on the first octet
    char ipClass;
    if (firstOctet >= 1 && firstOctet <= 126)
    {
        ipClass = 'A';
    }
    else if (firstOctet >= 128 && firstOctet <= 191)
    {
        ipClass = 'B';
    }
    else if (firstOctet >= 192 && firstOctet <= 223)
    {
        ipClass = 'C';
    }
    else if (firstOctet >= 224 && firstOctet <= 239)
    {
        ipClass = 'D';
    }
    else if (firstOctet >= 240 && firstOctet <= 255)
    {
        ipClass = 'E';
    }
    else
    {
        ipClass = 'I'; // Invalid class
    }

    // Checking if the IP address is private or public
    int isPrivate = 0;
    if (ipClass == 'A' && firstOctet == 10)
    {
        isPrivate = 1;
    }
    else if (ipClass == 'B' && firstOctet == 172)
    {
        int secondOctet;
        sscanf(ip, "%*d.%d", &secondOctet);
        if (secondOctet >= 16 && secondOctet <= 31)
        {
            isPrivate = 1;
        }
    }
    else if (ipClass == 'C' && firstOctet == 192)
    {
        int secondOctet;
        sscanf(ip, "%*d.%d", &secondOctet);
        if (secondOctet == 168)
        {
            isPrivate = 1;
        }
    }

    if (isPrivate)
    {
        printf("The IP address %s belong to class %c and is a private address\n", ip, ipClass);
    }
    else
    {
        printf("The IP address %s belong to class %c and is a public address\n", ip, ipClass);
    }

    return 0;
}

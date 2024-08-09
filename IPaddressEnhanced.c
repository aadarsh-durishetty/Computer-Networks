
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
uint32_t convertIPToDecimal(const char *ip_address)
{
       int a, b, c, d;
       sscanf(ip_address, "%d.%d.%d.%d", &a, &b, &c, &d);
       return (a << 24) | (b << 16) | (c << 8) | d;
}
void findAddressesAndSubnets(uint32_t ip_address, int subnet_bits)
{
       uint32_t subnet_mask = ~((1 << (32 - subnet_bits)) - 1);
       uint32_t network_address = ip_address & subnet_mask;
       uint32_t broadcast_address = network_address | ~subnet_mask;
       int num_subnets = 1 << (subnet_bits - 24);
       uint32_t subnet_1_start_address = network_address + 1;
       uint32_t subnet_1_last_address = broadcast_address - 1;
       printf("Class: C\n");
       printf("Broadcast Address: %u.%u.%u.%u\n",
              (broadcast_address >> 24) & 0xFF, (broadcast_address >> 16) & 0xFF,
              (broadcast_address >> 8) & 0xFF, broadcast_address & 0xFF);
       printf("Network Address: %u.%u.%u.%u\n",
              (network_address >> 24) & 0xFF, (network_address >> 16) & 0xFF,
              (network_address >> 8) & 0xFF, network_address & 0xFF);
       printf("Number of Subnets: %d\n", num_subnets);
       printf("Starting IP Address of Subnet 1: %u.%u.%u.%u\n",
              (subnet_1_start_address >> 24) & 0xFF, (subnet_1_start_address >> 16) & 0xFF,
              (subnet_1_start_address >> 8) & 0xFF, subnet_1_start_address & 0xFF);
       printf("Last IP Address of Subnet 1: %u.%u.%u.%u\n",
              (subnet_1_last_address >> 24) & 0xFF, (subnet_1_last_address >> 16) & 0xFF,
              (subnet_1_last_address >> 8) & 0xFF, subnet_1_last_address & 0xFF);
       printf("Usable IP range in subnet 1: %u.%u.%u.%u to %u.%u.%u.%u\n",
              ((subnet_1_start_address + 1) >> 24) & 0xFF, ((subnet_1_start_address + 1) >> 16) & 0xFF,
              ((subnet_1_start_address + 1) >> 8) & 0xFF, (subnet_1_start_address + 1) & 0xFF,
              ((subnet_1_last_address - 1) >> 24) & 0xFF, ((subnet_1_last_address - 1) >> 16) & 0xFF,
              ((subnet_1_last_address - 1) >> 8) & 0xFF, (subnet_1_last_address - 1) & 0xFF);
}
int main()
{
       char ip_address[16];
       printf("Enter the IP address ");
       scanf("%15s", ip_address);
       uint32_t ip_decimal = convertIPToDecimal(ip_address);
       int subnet_bits = 27;
       findAddressesAndSubnets(ip_decimal, subnet_bits);
       return 0;
}
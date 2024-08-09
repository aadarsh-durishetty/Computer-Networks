#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#define TIMEOUT 2
#define MAX_SEQ_NUM 1

typedef struct
{
    int seq;
    int ack;
    bool isLast;
} Packet;

void sendPacket(Packet packet)
{
    printf("Sending packet with seq=%d\n", packet.seq);
    sleep(1);
}

Packet receivePacket()
{
    Packet packet;
    printf("Enter received packet's seq (0 or 1): ");
    scanf("%d", &packet.seq);
    packet.ack = packet.seq;
    printf("Enter '1' to indicate the last packet, '0' otherwise: ");
    scanf("%d", (int *)&packet.isLast);
    return packet;
}

void simulateStopAndWaitARQ()
{
    int expectedSeq = 0;
    bool isLastPacketReceived = false;

    while (!isLastPacketReceived)
    {
        Packet sentPacket = {expectedSeq, -1, false};
        sendPacket(sentPacket);

        bool timeoutOccurred = false;
        Packet receivedPacket;

        // Simulate timeout by not receiving packet within TIMEOUT seconds
        if (rand() % 4 == 0)
        {
            printf("Timeout occurred.\n");
            timeoutOccurred = true;
        }
        else
        {
            receivedPacket = receivePacket();
        }

        if (!timeoutOccurred && receivedPacket.seq == expectedSeq)
        {
            printf("Received packet with seq=%d\n", receivedPacket.seq);
            expectedSeq = (expectedSeq + 1) % MAX_SEQ_NUM;
            isLastPacketReceived = receivedPacket.isLast;
        }
        else
        {
            printf("Packet loss or incorrect ACK. Resending packet.\n");
        }

        sleep(1);
    }

    printf("All packets received successfully.\n");
}

int main()
{
    srand(time(NULL));
    simulateStopAndWaitARQ();
    return 0;
}
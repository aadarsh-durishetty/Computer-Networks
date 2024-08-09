#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define PORT 8080
int main()
{
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    char message[1024] = "Hello from server!";
    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    // Set up server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    // Bind socket to address
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }
    // Listen for incoming connections
    if (listen(server_socket, 3) < 0)
    {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port %d...\n", PORT);
    // Accept incoming connection
    socklen_t client_addr_len = sizeof(client_addr);
    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_socket < 0)
    {
        perror("Accepting connection failed");
        exit(EXIT_FAILURE);
    }
    // Send message to client
    send(client_socket, message, strlen(message), 0);
    printf("Message sent to client: %s\n", message);
    // Close sockets
    close(client_socket);
    close(server_socket);
    return 0;
}

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "ws2_32.lib")  // Winsock library
#define PORT 1235       
#define MAX_PENDING 5
#define MAX_LINE 256

int f(int x) {
    return x * x;  // f(x) = x^2
}

int main() {
    WSADATA wsa;
    SOCKET s, new_s;
    struct sockaddr_in server, client;
    int client_len;
    int x, result;

    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET) {
        printf("Socket creation failed\n");
        WSACleanup();
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Bind failed\n");
        closesocket(s);
        WSACleanup();
        return 1;
    }

    listen(s, MAX_PENDING);
    printf("Server listening on port %d\n", PORT);

    client_len = sizeof(client);
    while (1) {
        new_s = accept(s, (struct sockaddr *)&client, &client_len);
        if (new_s == INVALID_SOCKET) {
            printf("Accept failed\n");
            continue;
        }

        if (recv(new_s, (char*)&x, sizeof(int), 0) <= 0) {
            printf("Recv failed\n");
            closesocket(new_s);
            continue;
        }

        printf("Received x = %d\n", x);

        result = f(x);

        send(new_s, (char*)&result, sizeof(int), 0);

        closesocket(new_s);
    }

    closesocket(s);
    WSACleanup();
    return 0;
}

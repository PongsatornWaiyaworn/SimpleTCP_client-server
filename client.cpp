#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "ws2_32.lib")  // Winsock library
#define PORT 1235 

int main(int argc, char *argv[]) {
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    int x, result;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s hostname x\n", argv[0]);
        exit(1);
    }

    char *host = argv[1];
    x = atoi(argv[2]);

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
    server.sin_port = htons(PORT);

    struct hostent *he = gethostbyname(host);
    if (he == NULL) {
        printf("Unknown host: %s\n", host);
        closesocket(s);
        WSACleanup();
        return 1;
    }
    memcpy(&server.sin_addr, he->h_addr_list[0], he->h_length);

    if (connect(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Connect failed\n");
        closesocket(s);
        WSACleanup();
        return 1;
    }

    send(s, (char*)&x, sizeof(int), 0);

    if (recv(s, (char*)&result, sizeof(int), 0) <= 0) {
        printf("Recv failed\n");
        closesocket(s);
        WSACleanup();
        return 1;
    }

    printf("f(%d) = %d\n", x, result);

    closesocket(s);
    WSACleanup();
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

#define MAX_LENGTH 1024

int main(int argc, char *argv[])
{
    if(argc != 4)
    {
        printf("Usage: %s <server-IP-address> <port> <file-streaming>\n", argv[0]);
        return 1;
    }
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));
    int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (client == -1)
    {
        perror("socket() failed");
        exit(EXIT_FAILURE);
    }
    if (connect(client, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("connect() failed");
        exit(EXIT_FAILURE);
    }
    printf("Connection to %s %s port [tcp/*] succeeded!\n", argv[1], argv[2]);

    FILE *fp = fopen(argv[3], "r");
    if(fp == NULL)
    {
        perror("fopen() failed");
        return 1;
    }

    char buf[21];
    memset(buf, 0, 21);
    while (!feof(fp))
    {
        fgets(buf, 21, fp);
        if(send(client, buf, strlen(buf), 0) == -1)
        {
            perror("send() failed");
            return 1;
        }
    }
    printf("Send successfully.\n");
    fclose(fp);
    close(client);
    return 0;

}
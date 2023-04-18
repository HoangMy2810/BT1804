#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

#define MAX_SIZE 1024
int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <server-IP-address> <port>\n", argv[0]);
        return 1;
    }
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));

    int client = socket(AF_INET, SOCK_STREAM, 0);
    if(client == -1)
    {
        perror("connect() failed");
        exit(EXIT_FAILURE);
    }
    printf("Connection to %s %s port [tcp/*] succeeded!\n", argv[1], argv[2]);
    char buf[MAX_SIZE];
    int pos = 0;
    memset(buf, 0, MAX_SIZE);

    char tenMT[MAX_SIZE];
    printf("Ten may tinh: ");
    fgets(tenMT, MAX_SIZE, stdin);
    tenMT[strcspn(tenMT, "\n")] = 0;

    strcpy(buf, tenMT);
    pos += strlen(tenMT);
    buf[pos] = 0;
    pos++;

    int soODia;
    printf("So o dia: ");
    scanf("%d", &soODia);
    getchar();

    char tenODia;
    int dungLuong;

    for(int i = 0; i < soODia; i++)
    {
        printf("Nhap ten o dia: ");
        scanf("%c", &tenODia);

        buf[pos] = tenODia;
        pos ++;

        printf("Nhap dung luong o dia: ");
        scanf("%d", &dungLuong);
        getchar();
        memcpy(buf + pos, &dungLuong, sizeof(dungLuong));
        pos += sizeof(dungLuong);
    }
    int bytes_sent = send(client, buf, pos, 0);
    if (bytes_sent == -1)
        {
            perror("send() failed");
            return 1;
        }
        printf("Send successfully\n\n");
    close(client);
    return 0;
}
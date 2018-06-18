/**
* 程序：server.c
* 目的：分配一个套接字，然后反复执行如下几步
        (1) 等待客户的下一个连接
        (2) 发送一个短消息给客户
        (3) 关闭与客户的连接
        (4) 转向 1
* 语法：server [port]
*           port - 服务器监听套接字所用的协议端口号
* 注意：参数是可选的，如果未指定端口号，客户机将使用 PROTOPORT 中给定的默认协议端口号
**/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <winsock.h>

#define PROTOPORT 5188  // 默认协议端口号
#define QLEN 6          // 连接请求缓冲区队列长度


int main(int argc, char *argv[])
{

    printf("Hello world!\n");

    struct sockaddr_in servaddr;
    struct sockaddr_in clientaddr;

    int listenfd;
    int clientfd;

    int port;
    int alen;   // 地址长度

    char buf[1000];     // 供服务器发送字符串所用的缓冲区

    static int visits = 0;         // 对客户机连接的计数

    memset(&servaddr, 0, sizeof servaddr);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;

    port = argc > 1 ? atoi(argv[1]) : PROTOPORT;
    if (port > 0 && port < 65536)
        servaddr.sin_port = htons((u_short)port);
    else
    {
        fprintf (stderr, "bad port number %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // 创建监听套接字

    WSADATA wsdata;
    WSAStartup(MAKEWORD(1,1), &wsdata);

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0)
    {
        fprintf(stderr, "socket creation failed: %lu\n", GetLastError());
        exit(EXIT_FAILURE);
    }

    // 绑定本地地址
    if ( bind(listenfd, (struct sockaddr *)&servaddr, sizeof servaddr)
         < 0)
    {
        fprintf(stderr, "bind failed\n");
        exit(EXIT_FAILURE);
    }

    // 开始监听，并指定监听套接字请求队列的长度
    if (listen(listenfd, QLEN))
    {
        fprintf(stderr, "listen failed\n");
        exit(EXIT_FAILURE);
    }

    while (true)
    {
        alen = sizeof(clientaddr);
        if (0 > (clientfd =
                 accept(listenfd, (struct sockaddr*)&clientaddr, &alen)))
        {
            fprintf(stderr, "accept failed\n");
            exit(EXIT_FAILURE);
        }

        visits++;

        sprintf(buf, "this server has been contacted %d time\n", visits);
        send(clientfd, buf, strlen(buf), 0);
        closesocket(clientfd);
    }
    WSACleanup();
    return 0;
}

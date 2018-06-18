/**
* 程序：client.c
* 目的：创建一个套接字，通过网络连接一个服务器，并打印来自服务器的信息
* 语法：client [host [port]]
*           host - 运行服务器的主机域名
*           port - 服务器监听套接字所用的协议端口号
* 注意：两个参数都是可选的。如果未指定主机名，客户机使用 localhost；
* 如果未指定端口号，客户机将使用 PROTOPORT 中给定的默认协议端口号
**/
#include <stdio.h>
#include <stdlib.h>

#include <winsock2.h>

#define PROTOPORT 5188  // 默认协议端口号
const char *localhost = "localhost";

int main(int argc, char *argv[])
{
    printf("Hello world!\n");
    struct hostent *ptrh;   // 指向主机列表中一个条目的指针
    struct sockaddr_in servaddr;    // 存放服务器端网络地址的结构
    int sockfd;     // 客户机端套接字描述符
    int port;       // 服务器端套接字协议端口号
    const char *host; // 服务器主机名
    int n;      // 读取的字符数
    char buf[1000];

    WSADATA wsdata;
    WSAStartup(MAKEWORD(2,2), &wsdata);

    memset(&servaddr, 0, sizeof servaddr);
    servaddr.sin_family = AF_INET;

    // 检查主机参数并指定主机名
    host = argc > 1 ? argv[1] : localhost;
    // 将主机名转换成相应的 IP 地址并复制到 servaddr 中
    ptrh = gethostbyname(host);     // 从服务器主机名获取相应的 IP 地址，
                                    // ptrh指向一个静态 hostent 对象
    if (ptrh == NULL)
    {
        fprintf(stderr, "invalid host: %s\n", host);
        exit(EXIT_FAILURE);
    }

    memcpy(&servaddr.sin_addr, ptrh->h_addr, ptrh->h_length);

    // 设置服务器监听套接字的端口号
    port = (argc > 2) ? atoi(argv[2]) : PROTOPORT;
    if (port > 0 && port <= 65535)
        servaddr.sin_port = htons((u_short)port);
    else
    {
        fprintf(stderr, "bad port number %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        fprintf(stderr, "socket creation failed\n");
        exit(EXIT_FAILURE);
    }
WSAAsyncSelect
    // 请求连接服务器
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof servaddr) < 0)
    {
        fprintf(stderr, "connect failed\n");    // 连接失败
        exit(EXIT_FAILURE);
    }

    // 从套接字反复读取数据，并输出到用户屏幕上
    while ((n = recv(sockfd, buf, sizeof buf, 0)) > 0)
    {
        //write( 1, buf, n);
        fwrite(buf, sizeof(*buf), n, stdout);
    }

    // 关闭套接字，并终止客户程序
    closesocket(sockfd);
    WSACleanup();
    return 0;
}

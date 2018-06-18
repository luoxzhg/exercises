#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <winsock2.h>

// 中断处理程序
void int_proc(int signo)
{ }

int main(int argc, char *argv[])
{
    printf("Hello world!\n");
    struct sockaddr_in  daddr;
    struct sockaddr_in  saddr;
    struct sockaddr_in  cmpaddr;
    int sockfd;
    int timer = 3;
    char buffer[1024];
    int addrlen, n;

    // 判断用户输入的命令是否正确
    if (argc != 5)
    {
        fprintf(stderr, "%s 目的IP 目的端口 源IP 源端口\n", argv[0]);
        exit(1);
    }

    // 设定中断处理函数，并设置时间限制
//    signal(SIGALRM, int_proc);
//    alarm(timer);

    // 建立数据报套接字
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2,2), &wsadata);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        fprintf(stderr, "socket error!\n");
        exit(1);
    }

    // 为结构变量 daddr 的各个字段赋值
    addrlen = sizeof(struct sockaddr_in);
    memset(&daddr, 0, addrlen);
    daddr.sin_family = AF_INET;
    daddr.sin_port = htons(atoi(argv[2]));
    if (inet_pton(AF_INET, argv[1], &daddr.sin_addr) <= 0)
    {
        fprintf(stderr, "Invalid dest IP!\n");
        exit(0);
    }

    // 为结构变量 saddr 的各个字段赋值
    addrlen = sizeof(struct sockaddr_in);
    memset(&saddr, 0, addrlen);
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[4]));
    if (inet_pton(AF_INET, argv[3], &saddr.sin_addr) <= 0)
    {
        fprintf(stderr, "Invalid source IP!\n");
        exit(0);
    }

    // 绑定地址
    if (bind(sockfd, (struct sockaddr*)&saddr, addrlen) < 0)
    {
        fprintf(stderr, "bind local addr error!\n");
        exit(1);
    }

    // 从标准输入获得字符串，并发送给目标地址
    if (fgets(buffer, 1024, stdin) == NULL)
        exit(0);

    if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&daddr, addrlen))
    {
        fprintf(stderr, "sendto error!\n");
        exit(2);
    }

    while (1)
    {
        n = recvfrom(sockfd, buffer, 1024, 0, &cmpaddr, &addrlen);
        if (n < 0)
        {
            //if (errno == EWOULDBLOCK)
            //{
             //   fprintf(stderr, "recvfrom timeout error!\n");
            //}
            //else
            //{
                fprintf(stderr, "recvfrom error!\n");
                exit(3);
            //}
        }
        else
        {
            // 比较数据报来源地址与保存的目标地址是否一致
            if (memcmp(cmpaddr, daddr, addrlen))
                continue;
            buffer[n] = '\0';
            printf("Received: %s", buffer);
        }

        // 从标准输入获得字符串，并发送给目标地址
        if (fgets(buffer, 1024, stdin) == NULL)
            exit(0);
        if (sendto(sockfd, buffer, strlen(buffer), 0, &daddr, addrlen))
        {
            fprintf(stderr, "sendto error!\n");
            exit(3);
        }

        //关闭套接字
        closesocket(sockfd);
        WSACleanup();
    }
    return 0;
}

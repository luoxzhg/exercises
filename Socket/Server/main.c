/**
* ����server.c
* Ŀ�ģ�����һ���׽��֣�Ȼ�󷴸�ִ�����¼���
        (1) �ȴ��ͻ�����һ������
        (2) ����һ������Ϣ���ͻ�
        (3) �ر���ͻ�������
        (4) ת�� 1
* �﷨��server [port]
*           port - �����������׽������õ�Э��˿ں�
* ע�⣺�����ǿ�ѡ�ģ����δָ���˿ںţ��ͻ�����ʹ�� PROTOPORT �и�����Ĭ��Э��˿ں�
**/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <winsock.h>

#define PROTOPORT 5188  // Ĭ��Э��˿ں�
#define QLEN 6          // �������󻺳������г���


int main(int argc, char *argv[])
{

    printf("Hello world!\n");

    struct sockaddr_in servaddr;
    struct sockaddr_in clientaddr;

    int listenfd;
    int clientfd;

    int port;
    int alen;   // ��ַ����

    char buf[1000];     // �������������ַ������õĻ�����

    static int visits = 0;         // �Կͻ������ӵļ���

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

    // ���������׽���

    WSADATA wsdata;
    WSAStartup(MAKEWORD(1,1), &wsdata);

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0)
    {
        fprintf(stderr, "socket creation failed: %lu\n", GetLastError());
        exit(EXIT_FAILURE);
    }

    // �󶨱��ص�ַ
    if ( bind(listenfd, (struct sockaddr *)&servaddr, sizeof servaddr)
         < 0)
    {
        fprintf(stderr, "bind failed\n");
        exit(EXIT_FAILURE);
    }

    // ��ʼ��������ָ�������׽���������еĳ���
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

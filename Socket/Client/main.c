/**
* ����client.c
* Ŀ�ģ�����һ���׽��֣�ͨ����������һ��������������ӡ���Է���������Ϣ
* �﷨��client [host [port]]
*           host - ���з���������������
*           port - �����������׽������õ�Э��˿ں�
* ע�⣺�����������ǿ�ѡ�ġ����δָ�����������ͻ���ʹ�� localhost��
* ���δָ���˿ںţ��ͻ�����ʹ�� PROTOPORT �и�����Ĭ��Э��˿ں�
**/
#include <stdio.h>
#include <stdlib.h>

#include <winsock2.h>

#define PROTOPORT 5188  // Ĭ��Э��˿ں�
const char *localhost = "localhost";

int main(int argc, char *argv[])
{
    printf("Hello world!\n");
    struct hostent *ptrh;   // ָ�������б���һ����Ŀ��ָ��
    struct sockaddr_in servaddr;    // ��ŷ������������ַ�Ľṹ
    int sockfd;     // �ͻ������׽���������
    int port;       // ���������׽���Э��˿ں�
    const char *host; // ������������
    int n;      // ��ȡ���ַ���
    char buf[1000];

    WSADATA wsdata;
    WSAStartup(MAKEWORD(2,2), &wsdata);

    memset(&servaddr, 0, sizeof servaddr);
    servaddr.sin_family = AF_INET;

    // �������������ָ��������
    host = argc > 1 ? argv[1] : localhost;
    // ��������ת������Ӧ�� IP ��ַ�����Ƶ� servaddr ��
    ptrh = gethostbyname(host);     // �ӷ�������������ȡ��Ӧ�� IP ��ַ��
                                    // ptrhָ��һ����̬ hostent ����
    if (ptrh == NULL)
    {
        fprintf(stderr, "invalid host: %s\n", host);
        exit(EXIT_FAILURE);
    }

    memcpy(&servaddr.sin_addr, ptrh->h_addr, ptrh->h_length);

    // ���÷����������׽��ֵĶ˿ں�
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
    // �������ӷ�����
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof servaddr) < 0)
    {
        fprintf(stderr, "connect failed\n");    // ����ʧ��
        exit(EXIT_FAILURE);
    }

    // ���׽��ַ�����ȡ���ݣ���������û���Ļ��
    while ((n = recv(sockfd, buf, sizeof buf, 0)) > 0)
    {
        //write( 1, buf, n);
        fwrite(buf, sizeof(*buf), n, stdout);
    }

    // �ر��׽��֣�����ֹ�ͻ�����
    closesocket(sockfd);
    WSACleanup();
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <winsock2.h>

// �жϴ������
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

    // �ж��û�����������Ƿ���ȷ
    if (argc != 5)
    {
        fprintf(stderr, "%s Ŀ��IP Ŀ�Ķ˿� ԴIP Դ�˿�\n", argv[0]);
        exit(1);
    }

    // �趨�жϴ�������������ʱ������
//    signal(SIGALRM, int_proc);
//    alarm(timer);

    // �������ݱ��׽���
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2,2), &wsadata);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        fprintf(stderr, "socket error!\n");
        exit(1);
    }

    // Ϊ�ṹ���� daddr �ĸ����ֶθ�ֵ
    addrlen = sizeof(struct sockaddr_in);
    memset(&daddr, 0, addrlen);
    daddr.sin_family = AF_INET;
    daddr.sin_port = htons(atoi(argv[2]));
    if (inet_pton(AF_INET, argv[1], &daddr.sin_addr) <= 0)
    {
        fprintf(stderr, "Invalid dest IP!\n");
        exit(0);
    }

    // Ϊ�ṹ���� saddr �ĸ����ֶθ�ֵ
    addrlen = sizeof(struct sockaddr_in);
    memset(&saddr, 0, addrlen);
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[4]));
    if (inet_pton(AF_INET, argv[3], &saddr.sin_addr) <= 0)
    {
        fprintf(stderr, "Invalid source IP!\n");
        exit(0);
    }

    // �󶨵�ַ
    if (bind(sockfd, (struct sockaddr*)&saddr, addrlen) < 0)
    {
        fprintf(stderr, "bind local addr error!\n");
        exit(1);
    }

    // �ӱ�׼�������ַ����������͸�Ŀ���ַ
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
            // �Ƚ����ݱ���Դ��ַ�뱣���Ŀ���ַ�Ƿ�һ��
            if (memcmp(cmpaddr, daddr, addrlen))
                continue;
            buffer[n] = '\0';
            printf("Received: %s", buffer);
        }

        // �ӱ�׼�������ַ����������͸�Ŀ���ַ
        if (fgets(buffer, 1024, stdin) == NULL)
            exit(0);
        if (sendto(sockfd, buffer, strlen(buffer), 0, &daddr, addrlen))
        {
            fprintf(stderr, "sendto error!\n");
            exit(3);
        }

        //�ر��׽���
        closesocket(sockfd);
        WSACleanup();
    }
    return 0;
}

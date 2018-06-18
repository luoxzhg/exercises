#include <stdio.h>
#include <stdlib.h>
#include "mydef.h"

int main(void)
{
    printf("Hello world!\n");
    printf("This program converts your time for a metric race to a time\n");
    printf("for running a mile and to your average speed in miles per hour.\n");

    printf("Please enter the distance run, in kilometres:\n");
    double  distk;
    scanf("%lf", &distk);

    printf("Next enter the time in minutes and seconds(mm:ss).\n");
    int mm, ss;
    scanf("%d:%d", &mm, &ss);

    // ��ʱ��ת��Ϊ��
    int sectime = mm * SEC_PER_MIN + ss;
    // �ѹ���ת��ΪӢ��
    double  distm = distk * MILE_PER_KM;
    printf("You run %.2f km (%.2f miles) in %d min, %d sec.\n", 
            distk, distm, mm, ss);
    
    // Ӣ��/Сʱ = Ӣ��/�� * ��/Сʱ
    double  speed = distm / sectime * SEC_PER_HOUR;
    
    // ÿӢ����ʱ = ʱ�� / Ӣ��
    sectime /= distm;

    mm = sectime / SEC_PER_MIN;
    ss = sectime % SEC_PER_MIN;

    printf("%d sec .\nYour average speed was %.2f mile/hour.\n",
           sectime, speed);
    return 0;
}

#include "myundef.h"

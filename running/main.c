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

    // 把时间转换为秒
    int sectime = mm * SEC_PER_MIN + ss;
    // 把公里转换为英里
    double  distm = distk * MILE_PER_KM;
    printf("You run %.2f km (%.2f miles) in %d min, %d sec.\n", 
            distk, distm, mm, ss);
    
    // 英里/小时 = 英里/秒 * 秒/小时
    double  speed = distm / sectime * SEC_PER_HOUR;
    
    // 每英里用时 = 时间 / 英里
    sectime /= distm;

    mm = sectime / SEC_PER_MIN;
    ss = sectime % SEC_PER_MIN;

    printf("%d sec .\nYour average speed was %.2f mile/hour.\n",
           sectime, speed);
    return 0;
}

#include "myundef.h"

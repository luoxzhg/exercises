#include <stdio.h>
#include <stdlib.h>

const int S_PER_M = 60;
const int S_PER_H = 3600;
const double M_PER_K = 0.62137;

int main(void)
{
    printf("Hello world!\n");
    double  distk, distm;  // distance run in km and in miles
    double rate;   // average speed in mph
    int min, sec;  // minutes and seconds of running time
    int time;      // running time in seconds only
    double  mtime; // time in seconds for one mile
    int mmin, msec; // minutes and seconds for one mile

    printf("This program converts your time for a metric race to a time\n"
           "for running a mile and to your average speed in miles per hour.\n");
    printf("Please enter, in kilometers, the distance run.\n");
    scanf("%lf", &distk);   // %lf for type double
    printf("Next enter the time in minutes and seconds.\n"
           "Begin by entering the minutes.\n");
    scanf("%d", &min);
    printf("Now enter the seconds.\n");
    scanf("%d", &sec);

    // converts time to pure seconds
    time = S_PER_M * min + sec;
    // converts kilometers to miles
    distm = M_PER_K * distk;
    // miles per sec * sec per per hour
    rate = distm / time * S_PER_H;
    // time per mile = time / distance
    mtime = (double)time / distm;
    mmin = (int)mtime / S_PER_M;   // find whole minutes
    msec = (int)mtime % S_PER_M;   // find remaining seconds
    printf("You ran %1.2f km (%1.2f miles) in %d min, %d sec.\n",
           distk, distm, min, sec);
    printf("That pace corresponds to running a mile in %d min, %d sec.\n",
            mmin, msec);
    printf("Your average speed was %1.2f mph.\n", rate);

    return 0;
}

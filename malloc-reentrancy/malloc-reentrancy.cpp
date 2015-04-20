#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>

int SetTimer()
{
    struct itimerval interval;

    interval.it_interval.tv_sec = 0;
    interval.it_interval.tv_usec = 1;
    interval.it_value.tv_sec = 1;
    interval.it_value.tv_usec = 0;

    if (::setitimer(ITIMER_REAL, &interval, NULL)) 
    {
        return -1;
    }    

    return 0;
}

void Handler(int nSigNo)
{
    printf("ALARM signal!\n");
    char *p = (char*)malloc(rand() % 40960);
        free(p);
}

int main()
{
    SetTimer();

    signal(SIGALRM, Handler);

    while (1)
    {
        char *p = (char*)malloc(rand() % 40960);
        free(p);
    }

    return 0;
}

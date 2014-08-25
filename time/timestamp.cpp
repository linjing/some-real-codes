#include <time.h>
#include <stdio.h>
int main ()
{
    char str[1024];
    time_t ts = time (NULL);
    strftime (str, sizeof(str)-1, "%Y-%m-%dT%H:%M:%S", gmtime (&ts));
    printf  ("%s\n", str);
    return 0;

}



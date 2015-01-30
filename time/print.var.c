#include <time.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_timezone_vars () {
//    extern char *tzname[2];
//    extern long timezone;
//    extern int daylight;
    printf ("tzname [%s]", tzname);
    printf ("timezone [%ld]", timezone);
    printf ("daylight [%d]\n", daylight);
}


int main () {

    show_timezone_vars ();

    char tz_buf[20] = "TZ=UTC";
    putenv (&tz_buf[0]);
    tzset ();

    show_timezone_vars ();

    char tz_buf2[20] = "TZ=CST-7";
    putenv (&tz_buf2[0]);
    tzset ();

    show_timezone_vars ();

    char copy_source[32];
    struct tm time_tm;
    memset (&time_tm, 0, sizeof (struct tm));
    strptime (copy_source, "%Y-%m-%d %H:%M:%S", &time_tm);
    time_t ret = mktime (&time_tm);
    (void) ret;

    show_timezone_vars ();

    return 0;
}

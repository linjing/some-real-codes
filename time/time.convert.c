#include <time.h>

#include <stdio.h>
#include <string.h>

const int year = 1900;
const int mon = 1;

time_t get_timestamp () {
    return time (NULL);
}

void show_tm (struct tm *m) {
    printf ("%04d:%02d:%02dT", m->tm_year + year, m->tm_mon + mon, m->tm_mday);
    printf ("%02d:%02d:%02d", m->tm_hour, m->tm_min, m->tm_sec);
    printf ("\n");
}

void tm_to_str (struct tm *m, char *buf) {
    sprintf (buf, "%04d-%02d-%02d %02d:%02d:%02d",
             m->tm_year + year, m->tm_mon + mon, m->tm_mday,
             m->tm_hour, m->tm_min, m->tm_sec);
}

void str_to_tm (char *buf, struct tm *m) {
    memset (m, 0, sizeof (struct tm));
    strptime (buf, "%Y-%m-%d %H:%M:%S", m);
}

int main () {
    time_t utc_ts = get_timestamp ();
    printf ("utc_ts %ld\n", utc_ts);

    const char *m1 = "convert utc to tm";
    printf ("%s\n", m1);
    struct tm gm;
    gmtime_r (&utc_ts, &gm);
    show_tm (&gm);

    const char *m11 = "convert utc to local tm";
    printf ("%s\n", m11);
    struct tm lm;
    localtime_r (&utc_ts, &lm);
    show_tm (&lm);

    const char *m2 = "convert tm to str";
    char buf2[32];
    tm_to_str (&gm, &buf2[0]);
    printf ("%s, buf [%s]\n", m2, buf2);

    const char *m21 = "convert local tm to str";
    char buf21[32];
    tm_to_str (&lm, &buf21[0]);
    printf ("%s, buf [%s]\n", m21, buf21);

    const char *m3 = "convert str to tm";
    struct tm gm2;
    str_to_tm (buf2, &gm2);
    printf ("%s:", m3);
    show_tm (&gm2);

    const char *m31 = "convert str(from local) to tm";
    struct tm lm2;
    str_to_tm (buf21, &lm2);
    printf ("%s:", m31);
    show_tm (&lm2);

    const char *m4 = "convert tm to utc [both]";
    time_t utc_1 = timegm (&gm2);
    time_t local_1 = timelocal (&lm2);
    printf ("%s, gm [%d], local [%d]\n", m4, utc_1, local_1);

    const char *m5 = "convert other timezone";
    time_t xx = timelocal (&gm2);
    printf ("%s, gm as local tm %d, zone %d \n", m5, xx, (utc_1-xx)/3600);

#define __USE_BSD 1
    printf ("printf zone info gm[%d][%s]\n", gm2.tm_gmtoff, gm2.tm_zone);
    printf ("printf zone info lm[%d][%s]\n", lm2.tm_gmtoff, lm2.tm_zone);

    const char *m6 = "format to str";
    char buf6[64];
    lm2.tm_gmtoff = 0*3600;
    strftime (&buf6[0], 64, "%G-%b-%d %H:%M:%S %z[%Z]", &lm2);
    printf ("%s, format %s\n", m6, buf6);
    
    const char *m7 = "format changed zone lm";
    time_t yy = timelocal (&lm2);
    printf ("%s, local tm to zone 0, calc utc seconds %d\n", m7, yy);

    return 0;
}

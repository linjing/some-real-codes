#include <time.h>
#include <stdio.h>
#include <string.h>

void format_time (); 
void use_ctime ();

int main ()
{
  format_time ();
  use_ctime ();
  return 0;
}

void use_ctime ()
{
  time_t ts = time (NULL);
  printf  ("Readable time: %s\n", ctime (&ts));
}

void format_time ()
{
  char str[1024];
  time_t ts = time (NULL);
  /* format time xxxx-xx-xxTxx:xx:xx */
  strftime (str, sizeof(str)-1, "%Y-%m-%dT%H:%M:%S", gmtime (&ts));
  printf  ("UTC time(3339): %s\n", str);

  struct tm tm_ts;
  strptime (str, "%Y-%m-%dT%H:%M:%S", &tm_ts);
  strftime (str, sizeof(str)-1, "%H:%M:%S %Y-%m-%d", &tm_ts);
  printf  ("UTC time [strf/ptime]: %s\n", str);
}

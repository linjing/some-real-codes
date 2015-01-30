#include <unistd.h>

#include <stdio.h>


int 
main ()
{
  printf ("page szie is %d\n", sysconf (_SC_PAGESIZE));
  return 0;
}

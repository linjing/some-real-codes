// test sizeof off_t
// 12/29/12 14:45:49

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main ()
{
    printf ("sizeof off_t %d\n", sizeof (off_t));
    printf ("sizeof fpos_t %d\n", sizeof (fpos_t));
    return 0;
}

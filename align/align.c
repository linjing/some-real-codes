#define _INTSIZEOF(n) ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )

#include <stdio.h>

int main () {
    printf ("%d, %d, %d, %d\n",
            _INTSIZEOF (float),
            _INTSIZEOF (double),
            _INTSIZEOF (char),
            _INTSIZEOF (char *)
           );
    return 0;
}


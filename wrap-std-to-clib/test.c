#include <stdio.h>

#include "cmap.h"
int main ()
{
    my_map_t *p;
    p = my_create_map ();
    if (p == NULL) {
        printf ("my_create_map failed\n");
        return 0;
    }
    int ret = my_map_set (p, 1, 2);
    if (ret == -1) {
        printf ("my_map_set failed\n");
        return 0;
    }

    unsigned v;
    ret = my_map_exist (p, 1);
    if (ret == -1) {
        printf ("my_map not exist \n");
        return 0;
    }
    ret = my_map_get (p, 1, &v);
    if (ret == -1) {
        printf ("my_map_get failed\n");
        return 0;
    }
    printf ("get key 1 is %d\n", v);
    return 0;
}

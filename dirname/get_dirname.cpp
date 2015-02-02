#include <libgen.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main (int argc, char **argv)
{
    char *path = strdup (argv[0]);
    char *p = dirname (path);
    printf ("bin path %s\n", p);
    free (path);

    char *cur_dir = get_current_dir_name ();
    printf ("cur path %s\n", cur_dir);
    free (cur_dir);
    return 0;
}


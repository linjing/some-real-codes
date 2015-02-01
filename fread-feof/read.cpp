// read.cpp: test feof & ferror
// 2012年12月12日 09时56分43秒

#include <stdio.h>

struct A {
    char a[4];
};

int main (int argc, char **argv) {
    if (argc < 2) {
        printf ("useage: %s file-name\n", argv[0]);
        return 0;
    }

    printf ("sizeof A %d\n", sizeof (struct A));

    char *filename = argv[1];
    FILE *fp = fopen (filename, "r");
    if (!fp) {
        printf ("open failed %s\n", filename);
        return 0;
    }

    do {
        struct A a;
        int ret = fread (&a, sizeof (a), 1, fp);
        printf ("fread return %d\n", ret);
        if (ret != 1) {
            int err = ferror (fp);
            int eof = feof (fp);
            printf ("err %d eof %d\n", err, eof);
            if (err == 0) {
                clearerr (fp);
                int ret = fread (&a, 1, 1, fp);
                printf ("fread return %d\n", ret);
                if (ret != 1) {
                    int err = ferror (fp);
                    int eof = feof (fp);
                    printf ("@err %d eof %d\n", err, eof);
                }
            }
            break;
        }
    } while (true);

    fclose (fp);
    return 0;
}


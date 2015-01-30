#include <stdio.h>

#pragma pack (push, 1)
typedef struct pack1_s {
    char a;
    double b;
    int c;
} pack1_t;
#pragma pack (pop)

#pragma pack (push, 2)
typedef struct pack2_s {
    char a;
    double b;
    int c;
} pack2_t;
#pragma pack (pop)


typedef struct pack_default_s {
    char a;
    double b;
    int c;
} pack_default_t;

int main () {
    printf ("show struct size with pack {char, double, int}\n");
    printf ("size of pack1[%d] pack2[%d] pack_default[%d]\n",
            sizeof (pack1_t), sizeof (pack2_t), sizeof (pack_default_t));
    return 0;
}

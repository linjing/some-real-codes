#include <assert.h>
#include <printf.h>
#include <stdarg.h>
#include <stdio.h>

#define ARG_MAX_LEN 1000

void info () {
    printf ("PA_FLAG_MASK\t\t %04hx\n", PA_FLAG_MASK);
    printf ("~PA_FLAG_MASK\t\t %04hx\n", ~PA_FLAG_MASK);

    printf ("conversion specifier\t args & ~PA_FLAG_MASK\n");
    printf ("flags\t\t\t arg & PA_FLAG_MASK\n");

    printf ("PA_INT\t\t\t %04hx\n", PA_INT);
    printf ("PA_CHAR\t\t\t %04hx\n", PA_CHAR);
    printf ("PA_STRING\t\t %04hx\n", PA_STRING);
    printf ("PA_POINTER\t\t %04hx\n", PA_POINTER);
    printf ("PA_FLOAT\t\t %04hx\n", PA_FLOAT);
    printf ("PA_DOUBLE\t\t %04hx\n", PA_DOUBLE);

    printf ("PA_FLAG_LONG_LONG\t %04hx\n", PA_FLAG_LONG_LONG);
    printf ("PA_FLAG_LONG\t\t %04hx\n", PA_FLAG_LONG);
    printf ("\n\n");
}

short int get_conversion_specifier (short pa) {
    return pa & ~PA_FLAG_MASK;
}
short int get_flag (short pa) {
    return pa & PA_FLAG_MASK;
}
void test_print_format (const char *fmt) {
    printf ("test format [%s]\n", fmt);
    int args[ARG_MAX_LEN];
    int arg_no = parse_printf_format (fmt, ARG_MAX_LEN, args);
    for (int i = 0; i < arg_no; ++i)
        printf ("\t%d arg: %x\n", i, args[i]);
}

void skip_args_impl (const char *first_arg, va_list al) {
    const char *fmt = first_arg;
    do {
        int args[ARG_MAX_LEN];
        int arg_no = parse_printf_format (fmt, ARG_MAX_LEN, args);
        if (arg_no == 0) break;
        test_print_format (fmt);

        for (int i = 0; i < arg_no; ++i) {
            short int type = get_conversion_specifier (args[i]);
            short int flag = get_flag (args[i]);
            printf ("type %hx, flag %hx\n", type, flag);
            switch (type) {
            case PA_INT:
                if (flag == PA_FLAG_LONG_LONG)
                    (void) va_arg (al, long long);
                else if (flag == PA_FLAG_LONG)
                    (void) va_arg (al, long);
                else
                    (void) va_arg (al, int);
                break;
            case PA_CHAR:
                (void) va_arg (al, int);
                break;
            case PA_STRING:
                (void) va_arg (al, char *);
                break;
            case PA_POINTER:
                (void) va_arg (al, void *);
                break;
            case PA_FLAG_LONG_LONG:
                (void) va_arg (al, long long);
                break;
            case PA_FLOAT:
                // FALLTHROUGH
            case PA_DOUBLE: // TO MAKE SURE long is double type base
                (void) va_arg (al, double);
                break;
            default:
                printf ("unsupport type\n");
                assert (0);
            }
        }
        fmt = va_arg (al, char *);
    } while (1);
}

void skip_args (const char *fmt, ...) {
    va_list al;
    va_start (al, fmt);
    printf ("call skip_args_impl\n");
    skip_args_impl (fmt, al);
    va_end (al);
}

int main () {
    info ();
    test_print_format ("%2.3f");
    test_print_format ("%2.3d");
    test_print_format ("%s");
    test_print_format ("%2.3f %2d %s %lld %2u");

    skip_args ("%2.3f %2d %s %lld %2u",
               (float) 2, (int) 2, "hello", (long long) 2, (unsigned) 2,
               "%2.3f %2d %s %lld %2u %zi",
               (float) 2, (int) 2, "hello", (long long) 2, (unsigned) 2, (size_t) 2);


    return 0;
}

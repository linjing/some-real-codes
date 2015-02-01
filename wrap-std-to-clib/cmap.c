#include "cmap.h"
#include "cmap.hpp"

#include <stdio.h>

extern "C" {

void *my_create_map () {
    return (void *) my_create_map_impl ();
}

int my_map_set (void *p, unsigned long key, unsigned value) {
    return my_map_set_impl (p, key, value);
}

int my_map_get (void *p, unsigned long key, unsigned *value) {
    return my_map_get_impl (p, key, value);
}

int my_map_exist (void *p, unsigned long key) {
    return my_map_exist_impl (p, key);
}

void my_map_free (void *p) {
    my_map_free_impl (p);
}

}

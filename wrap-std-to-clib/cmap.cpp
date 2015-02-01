#include "cmap.hpp"

#include <stdio.h>
#include <map>

using namespace std;

struct my_map_s {
    std::map<unsigned long, unsigned> map_impl;
};

typedef struct my_map_s *my_map_t;

void *my_create_map_impl () {
    struct my_map_s *p = NULL;
    try {
        p = new struct my_map_s;
    } catch (...) {
        return (void *) NULL;
    }
    return (void *)p;
}

int my_map_set_impl (void *p, unsigned long key, unsigned value) {
    struct my_map_s *m = (struct my_map_s *) p;
    if (m == NULL)
        return -1;
    try {
        m->map_impl[key] = value;
    } catch (...) {
        return -1;
    }
    return 0;
}

int my_map_get_impl (void *p, unsigned long key, unsigned *value) {
    struct my_map_s *m = (struct my_map_s *) p;
    if (m == NULL || value == NULL)
        return -1;

    try {
        *value = m->map_impl[key];
    } catch (...) {
        return -1;
    }
    return 0;
}

int my_map_exist_impl (void *p, unsigned long key) {
    struct my_map_s *m = (struct my_map_s *) p;
    if (m == NULL)
        return -1;

    try {
        if (m->map_impl.find (key) == m->map_impl.end ())
            return -1;
        else
            return 0;
    } catch (...) {
        return -1;
    }
}

void my_map_free_impl (void *p) {
    delete (struct my_map_s *)p;
}

int my_map_increase_impl (void *p, unsigned long key, unsigned value) {
    struct my_map_s *m = (struct my_map_s *) p;
    if (m == NULL)
        return -1;

    try {
        if (m->map_impl.find (key) == m->map_impl.end ())
            return m->map_impl[key] = value;
        else
            return m->map_impl[key] += value;
    } catch (...) {
        return -1;
    }
}

int my_map_size_impl (void *p) {
    struct my_map_s *m = (struct my_map_s *) p;
    if (m == NULL)
        return -1;
    return (int) (m->map_impl.size ());
}

int my_map_next_impl (void *p, unsigned long pre_key, unsigned long *key, unsigned *value) {
    struct my_map_s *m = (struct my_map_s *) p;
    if (m == NULL || key == NULL ||  value == NULL)
        return -1;

    try {
        if (pre_key == 0) {
            *key = m->map_impl.begin ()->first;
            *value = m->map_impl.begin ()->second;
            return 0;
        }

        std::map<unsigned long, unsigned>::iterator it = m->map_impl.find (pre_key);
        if (it == m->map_impl.end ())
            return -1;
        ++ it;
        if (it == m->map_impl.end ())
            return -1;
        *key = it->first;
        *value = it->second;
    } catch (...) {
        return -1;
    }
    return 0;
}

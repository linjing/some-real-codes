#ifndef ___MY_CMAP_HPP__
#define ___MY_CMAP_HPP__

    extern void *my_create_map_impl ();
    extern int my_map_set_impl (void *p, unsigned long key, unsigned value);
    extern int my_map_get_impl (void *p, unsigned long key, unsigned *value);
    extern int my_map_exist_impl (void *p, unsigned long key);
    extern void my_map_free_impl (void *p);

    extern int my_map_add_impl (void *p, unsigned long key, unsigned value);
    extern int my_map_size_impl (void *p);
    extern int my_map_next_impl (void *p, unsigned long pre_key, unsigned long *key, unsigned *value);



#endif // #ifndef __CMAP_H__

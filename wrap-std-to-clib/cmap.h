#ifndef ___MY_CMAP_H__
#define ___MY_CMAP_H__


#ifdef __cplusplus
extern "C" {
#endif

    typedef void * my_map_t;

    extern my_map_t my_create_map ();
    extern int my_map_set (my_map_t p, unsigned long key, unsigned value);
    extern int my_map_get (my_map_t p, unsigned long key, unsigned *value);
    extern int my_map_exist (my_map_t p, unsigned long key);

#ifdef __cplusplus
}
#endif



#endif // #ifndef __CMAP_H__

#include <cassert>
#include <cstdio>

#include "hello.hpp"

//#if defined(__MINGW32__)
//  #include <windows.h>
//  #define dlopen(a,b) LoadLibrary(a)
//  #define dlsym(a,b) GetProcAddress(a,b)
//  #define dlerror GetLastError
//  #define dlclose(a) FreeLibrary(a)
//#else
//  #include <dlfcn.h>
//#endif
#include <dlfcn.h>

int load_lib (void **handler, const char *lib) {
  assert (lib != NULL);
  *handler = dlopen (lib, RTLD_NOW);
  if (*handler == NULL)
    return -1;
  return 0;
}

void release (void *handler) {
  dlclose (handler);
}

int main (int argc, char **args) {
  if (argc < 2) {
    printf ("usage: %s lib_name\n\n", args[0]);
    return 0;
  }
  void *handler;
  int ret = load_lib (&handler, args[1]);
  if (ret < 0) {
    printf ("load lib %s failed\n", args[1]);
    return 1;
  }

  const char *fun_name = "say_hello";
  void (*p_say_hello) (const char *);
  p_say_hello = (void (*)(const char *))dlsym (handler, fun_name);
  if (p_say_hello == NULL) {
    printf ("function %s not exist\n", fun_name);
    return 1;
  }

  p_say_hello  ("linjing");

  release (handler);
  return 0;
}

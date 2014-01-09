#include "hello.hpp"

#include <cstdio>
using namespace std;

void say_hello (const char *somebody) {
  printf ("hello %s\n", somebody);
  printf ("\t\t\t\t -- printf\n");
}

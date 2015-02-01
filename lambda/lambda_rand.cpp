#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include <functional>
#include <iostream>
#include <algorithm>
using namespace std;


struct add_x {
 int &x_;
 add_x (int x) : x_ (x) {}
 int operator () (int y) { return y + x_; }
};

struct eq_x {
 int x_;
 eq_x (int x) : x_ (x) {}
 bool operator () (int y, int z) { if (y == x_) return y == z; else return false; }
};

void test_1 () {
  cout << "test 1" << endl;
  int x[10];
  std::generate (&x[0], &x[10], [] () { struct timeval t; gettimeofday (&t, NULL); srand (t.tv_usec);  return (int) (rand () % 4); });
  std::for_each (&x[0], &x[10], [] (int x) { cout << x << " "; });
  cout << endl;
  eq_x xxxx (2);
  std::sort (&x[0], &x[10]);
  auto it = std::unique (&x[0], &x[10], xxxx);
  std::for_each (&x[0], it, [] (int x) { cout << x << " "; });
  cout << endl;
}

bool eq_fun (int y, int z, int x_) {
 if (y == x_) return y == z; else return false; 
}

void test_2 () {
  cout << "test 2" << endl;
  int x[10];
  std::generate (&x[0], &x[10], [] () { struct timeval t; gettimeofday (&t, NULL); srand (t.tv_usec);  return (int) (rand () % 4); });
  std::for_each (&x[0], &x[10], [] (int x) { cout << x << " "; });
  cout << endl;
  int x_ = 2;
  std::sort (&x[0], &x[10]);
  auto eq_fun_x = std::bind (eq_fun, std::placeholders::_1, std::placeholders::_2, x_);
  auto it = std::unique (&x[0], &x[10], eq_fun_x);
  std::for_each (&x[0], it, [] (int x) { cout << x << " "; });
  cout << endl;
}

void test_3 () {
  cout << "test 3" << endl;
  int x[10];
  std::generate (&x[0], &x[10], [] () { struct timeval t; gettimeofday (&t, NULL); srand (t.tv_usec);  return (int) (rand () % 4); });
  std::for_each (&x[0], &x[10], [] (int x) { cout << x << " "; });
  cout << endl;
  int x_ = 2;
  std::sort (&x[0], &x[10]);
  auto it = std::unique (&x[0], &x[10], [x_] (int y, int z) -> bool {if (y == x_) return y == z; else return false;});
  std::for_each (&x[0], it, [] (int x) { cout << x << " "; });
  cout << endl;
}

int main (int argc, char **argv) {
  
  test_1 ();
  test_2 ();
  test_3 ();
   
  return 0;
}

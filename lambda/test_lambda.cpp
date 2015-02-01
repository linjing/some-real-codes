#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

// lambda used as friend for class, by defined in class
// can access private member
class T {
public:
  T (int x) : i_am_private (0) {
    [this] (int x) { this->i_am_private = x*x; } (x);
    cout << i_am_private << endl;
  }
private:
  int i_am_private;
};

int main (int argc, char **args) {
  // with return type
  int n = [] (int x, int y) -> int { return x + y; } (1, 2);
  cout << n << endl;

  // without return type
  n = [] (int x, int y) { return x + y; } (1, 2);
  cout << n << endl;

  // test [] = (by value)  & (by ref)
{
  int a = 1; int b = 1;
  n = [&] () -> int { a++; b++; return a+b; } ();
  cout << a << " " << b << " " << n << endl;
}
{
  int a = 1; int b = 1;
  // b++ // error: increment of read-only variable ‘b’ 
  n = [&, b] () -> int { a++; b/*++*/; return a+b; } ();
  cout << a << " " << b << " " << n << endl;
}
  // work with std::for_each
  // () for argment is not needed 
{
  int a[3] = {1,2,3};
  int n = 0;
  std::for_each (&a[0], &a[3], [&n] (int x) { n += x;});
  cout << "1+2+3= " << n << endl;
}
  // test bambda in class
  T t (5);

  // use std::function, to use lambda as an argment
{
  int n = 1;
  int i = 3;
  auto myp_lambda = new auto ([&] (int x) -> int {n += x;});
  auto my_lambda = [&] (int x) -> int { return n += x;};
  // test_lambda.cpp:55:34: error: ‘my_lambda’ cannot be used as a function
  //std::reference_closure<void()> myLambdaFunc = []() { cout << "haha" << endl; }
  cout << "1+3 =" <<  my_lambda (i) << endl;
  //cout << "1+3 =" <<  myp_lambda (i) << endl;
}
{
  // x will be 1, y will be 4 in lambda
  int x = 1, y = 2;
  auto f1 = [x, &y] () -> int { return x + y; };
  x = 3, y = 4;
  cout << "f1 = " << f1 () << endl;
}
  return 0;
}

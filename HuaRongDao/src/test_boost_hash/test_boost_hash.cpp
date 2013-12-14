#include <boost/functional/hash/hash.hpp>

#include <iostream>

using namespace std;

void test_hash_value () {
  cout << "test boost::hash_value" << endl;
  cout << "boost::hash_value ((int) 6) = " << boost::hash_value ((int) 6) << endl;
  cout << "boost::hash_value ((int) 66) = " << boost::hash_value ((int) 66) << endl;
}

void test_hash_combine () {
  cout << "test boost::hash_combine" << endl;
  size_t seed = 9;
  boost::hash_combine<int> (seed, (int) 1);
  cout << "boost::hash_combine seed(9) (1) = " << seed << endl;
}

void test_hash_range () {
  cout << "test boost::hash_range" << endl;
  int a[2] = {1,2};
  cout << "boost::hash_range (1,2) = " << boost::hash_range (&a[0], &a[2]) << endl;
}
int main (int argc, char **argv) {
  test_hash_value ();
  test_hash_combine ();
  test_hash_range ();
  return 0;
}

#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

#include <boost/functional/hash/hash.hpp>

struct mask {
  string str;
  size_t hash_value () const {
    //return std::hash_range (str.begin (), str.end ());
    return boost::hash_range (str.begin (), str.end ());
  }
};

namespace std {
  template <>
  struct hash<mask> {
    size_t operator () (const mask &m) const {
      return m.str.size ();
    }
  };

  template <>
  struct equal_to<mask> : public binary_function<mask, mask, bool> {
    bool operator () (const mask &l, const mask &r) const {
      return l.hash_value () == r.hash_value ();
//      std::hash<mask> hasher;
//      size_t lh = hasher (l); size_t rh = hasher (r);
//      return lh == rh;
    }
  };
}

int main (int argc, char **argv) {
  unordered_set<mask> masks;
  mask a; a.str = "hello";
  mask b;
  if (argc == 1)
    b.str = "hello";
  else
    b.str = argv[1];

  cout << "a:" << a.hash_value () << endl;
  cout << "b:" << b.hash_value () << endl;

  masks.insert (a);
  auto res = masks.insert (b);
  if (res.second)
    cout << "not found" << endl;
  else
    cout << "found" << endl;

  return 0;
}
